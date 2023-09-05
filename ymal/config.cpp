#include "config.h"
ConfigParser::ConfigParser(const std::string& filename) : filename_(filename) {}

bool ConfigParser::parse() {
    std::ifstream fin(filename_);
    if (!fin) {
        std::cerr << "Failed to open the YAML file." << std::endl;
        return false;
    }

    YAML::Node config = YAML::Load(fin);

    try {
        modelConfig_.name = config["name"].as<std::string>();
        modelConfig_.source_type = config["SOURCE"]["source_type"].as<std::string>();
        modelConfig_.decoder_out_width = config["SOURCE"]["decoder_out_width"].as<int>();
        modelConfig_.decoder_out_height = config["SOURCE"]["decoder_out_height"].as<int>();

        // Parse RtspSourceConfig (if needed)
        if(!parseRtspSource(config["SOURCE"]["RTSP_SOURCE"], modelConfig_.rtsp_source_config,modelConfig_.source_type)){
             std::cout <<"parseRtspSource" <<std::endl;
            return false;
        }

        modelConfig_.algorithm = config["RUNTIME"]["algorithm"].as<std::string>();
        modelConfig_.model_type = config["RUNTIME"]["model_type"].as<std::string>();
        modelConfig_.model_in_path = config["RUNTIME"]["model_in_path"].as<std::string>();

        modelConfig_.sink_type = config["SINK"]["sink_type"].as<std::string>();

        // Parse MqttSinkConfig (if needed)
        if(parseMqttSink(config["SINK"]["MQTT_SINK"], modelConfig_.mqtt_sink_config,modelConfig_.sink_type)){

        }// Parse HttpSinkConfig (if needed)
        else if(parseHttpSink(config["SINK"]["HTTP_SINK"], modelConfig_.http_sink_config,modelConfig_.sink_type)){

        }else{
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing YAML: " << e.what() << std::endl;
        return false;
    }

    return true;
}

const ModelConfig& ConfigParser::getModelConfig() const {
    return modelConfig_;
}



bool ConfigParser::parseRtspSource(const YAML::Node& sourceNode, RtspSourceConfig& rtspConfig,const std::string& source_type){
    if(source_type.compare("rtsp_source")==0){
        modelConfig_.rtsp_source_config.rtsp_source_uris = sourceNode["rtsp_source_uris"].as<std::string>();
        return true;
    }
    return false;
}
bool ConfigParser::parseMqttSink(const YAML::Node& sinkNode, MqttSinkConfig& mqttConfig,const std::string& sink_type){
    if(sink_type.compare("mqtt_sink")==0){
        modelConfig_.mqtt_sink_config.sink_ip = sinkNode["sink_ip"].as<std::string>();
        modelConfig_.mqtt_sink_config.sink_port = sinkNode["sink_port"].as<int>();
        modelConfig_.mqtt_sink_config.sink_original_img = sinkNode["sink_original_img"].as<bool>();
        modelConfig_.mqtt_sink_config.mqtt_qos = sinkNode["mqtt_qos"].as<int>();
        return true;
    }
    return false;

}
bool ConfigParser::parseHttpSink(const YAML::Node& sinkNode, HttpSinkConfig& httpConfig,const std::string& sink_type){
    if(sink_type.compare("http_sink")==0){
        modelConfig_.http_sink_config.http_sink_uri = sinkNode["http_sink_uri"].as<std::string>();
        return true;
    }
    return false;
}