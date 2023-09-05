#include "ConfigParser.h"
#include <fstream>
#include <iostream>

ConfigParser::ConfigParser(const std::string& filename) : filename(filename) {}

const ModelConfig& ConfigParser::getModelConfig() const {
    return modelConfig_;
}


bool ConfigParser::loadConfig() {
    std::ifstream jsonFile(filename);
    if (!jsonFile.is_open()) {
        std::cerr << "Error opening JSON file: " << filename << std::endl;
        return false;
    }

    jsonFile >> jsonData;
    jsonFile.close();
    if(parse()){
        return true;
    }
    return false;
    
}

bool ConfigParser::parse(){
    modelConfig_.name=getName();
    modelConfig_.source_type= getSourceType();
    modelConfig_.decoder_out_width=getDecoderOutWidth();
    modelConfig_.decoder_out_height=getDecoderOutHeight();
    modelConfig_.is_video=getIsVideo();

    if(modelConfig_.source_type.compare("rtsp_source")==0){
        modelConfig_.rtsp_source_config.rtsp_source_uris=getRTSPSourceURIs();
    }
    modelConfig_.algorithm= getAlgorithm();
    modelConfig_.model_type= getModelType();
    modelConfig_.model_in_path=getModelInPath();
    modelConfig_.class_names=getClassNames();
    modelConfig_.sink_type=getSinkType();
    if(modelConfig_.sink_type.compare("mqtt_sink")==0){
        modelConfig_.mqtt_sink_config.sink_ip=getSinkIP();
        modelConfig_.mqtt_sink_config.sink_port=getSinkPort();
        modelConfig_.mqtt_sink_config.sink_original_img=getSinkOriginalImg();
        modelConfig_.mqtt_sink_config.mqtt_qos=getMQTTQoS();
    }else if(modelConfig_.sink_type.compare("http_sink")==0){
        modelConfig_.http_sink_config.http_sink_uri=getHttpSinkURI();
        modelConfig_.http_sink_config.http_sink_endpoint=getHttpSinkEndpoint();
    }
    return true;
}

std::string ConfigParser::getName() const {
    return jsonData["name"].get<std::string>();
}

std::string ConfigParser::getSourceType() const {
    return jsonData["source"]["sourceType"].get<std::string>();
}

int ConfigParser::getDecoderOutWidth() const {
    return jsonData["source"]["decoderOutWidth"].get<int>();
}

int ConfigParser::getDecoderOutHeight() const {
    return jsonData["source"]["decoderOutHeight"].get<int>();
}


bool ConfigParser::getIsVideo() const {
    return jsonData["source"]["isVideo"].get<int>();
}

std::string ConfigParser::getRTSPSourceURIs() const {
    return jsonData["source"]["rtspSource"]["rtspSourceUris"].get<std::string>();
}

std::string ConfigParser::getAlgorithm() const {
    return jsonData["runtime"]["algorithm"].get<std::string>();
}

std::string ConfigParser::getModelType() const {
    return jsonData["runtime"]["modelType"].get<std::string>();
}

std::string ConfigParser::getModelInPath() const {
    return jsonData["runtime"]["modelInPath"].get<std::string>();
}

std::vector<std::string> ConfigParser::getClassNames() const {
    return jsonData["runtime"]["classNames"].get<std::vector<std::string>>();
}

std::string ConfigParser::getSinkType() const {
    return jsonData["sink"]["sinkType"].get<std::string>();
}

std::string ConfigParser::getSinkIP() const {
    return jsonData["sink"]["mqttSink"]["sinkIp"].get<std::string>();
}

int ConfigParser::getSinkPort() const {
    return jsonData["sink"]["mqttSink"]["sinkPort"].get<int>();
}

bool ConfigParser::getSinkOriginalImg() const {
    return jsonData["sink"]["mqttSink"]["sinkOriginalImg"].get<bool>();
}

int ConfigParser::getMQTTQoS() const {
    return jsonData["sink"]["mqttSink"]["mqttQos"].get<int>();
}

std::string ConfigParser::getHttpSinkURI() const {
    return jsonData["sink"]["httpSink"]["httpSinkUri"].get<std::string>();
}

std::string ConfigParser::getHttpSinkEndpoint() const {
    return jsonData["sink"]["httpSink"]["httpSinkEndpoint"].get<std::string>();
}
