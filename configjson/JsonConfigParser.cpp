#include "JsonConfigParser.h"
#include <fstream>
#include <iostream>

JsonConfigParser::JsonConfigParser() {}


bool JsonConfigParser::loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    Json::CharReaderBuilder builder;
    Json::Value jsonData;
    std::string errs;
    if (!Json::parseFromStream(builder, file, &jsonData, &errs)) {
        std::cerr << "Error parsing JSON: " << errs << std::endl;
        return false;
    }

    root = jsonData;
    parse();
    return true;
}

bool JsonConfigParser::parse(){
    modelConfig_.name=getString("name");
    modelConfig_.source_type= getString("SOURCE","source_type","");
    modelConfig_.decoder_out_width=getInt("SOURCE","decoder_out_width",0);
    modelConfig_.decoder_out_height=getInt("SOURCE","decoder_out_height",0);

    if(modelConfig_.source_type.compare("rtsp_source")==0){
        modelConfig_.rtsp_source_config.rtsp_source_uris=getString("SOURCE","RTSP_SOURCE","rtsp_source_uris","");
    }
    modelConfig_.algorithm= getString("RUNTIME","algorithm","");
    modelConfig_.model_type= getString("RUNTIME","model_type","");
    modelConfig_.model_in_path=getString("RUNTIME","model_in_path","");
    modelConfig_.class_in_path=getString("RUNTIME","class_in_path","");
    modelConfig_.sink_type=getString("RUNTIME","sink_type","");
    if(modelConfig_.sink_type.compare("mqtt_sink")==0){
        modelConfig_.mqtt_sink_config.sink_ip=getString("SINK","MQTT_SINK","sink_ip","");
        modelConfig_.mqtt_sink_config.sink_port=getInt("SINK","MQTT_SINK","sink_port",0);
        modelConfig_.mqtt_sink_config.sink_original_img=getInt("SINK","MQTT_SINK","sink_original_img",0);
        modelConfig_.mqtt_sink_config.mqtt_qos=getInt("SINK","MQTT_SINK","mqtt_qos",0);
    }else if(modelConfig_.sink_type.compare("http_sink")==0){
        modelConfig_.http_sink_config.http_sink_uri=getString("SINK","HTTP_SINK","http_sink_uri","");
        modelConfig_.http_sink_config.http_sink_endpoint=getString("SINK","HTTP_SINK","http_sink_endpoint","");
    }
    return true;
}


const ModelConfig& JsonConfigParser::getModelConfig() const {
    return modelConfig_;
}

int JsonConfigParser::getInt(const std::string& key, int defaultValue) const {
    if (root.isMember(key) && root[key].isInt()) {
        return root[key].asInt();
    }
    return defaultValue;
}
int JsonConfigParser::getInt(const std::string& key,const std::string& key2, int defaultValue) const {
    if (root.isMember(key) && root[key].isMember(key2) &&  root[key][key2].isInt()) {
        return root[key][key2].asInt();
    }
    return defaultValue;
}
int JsonConfigParser::getInt(const std::string& key,const std::string& key2,const std::string& key3,int defaultValue) const {
    if (root.isMember(key) && root[key].isMember(key2) && root[key][key2].isMember(key3) && root[key][key2][key3].isInt()) {
        return root[key][key2][key3].asInt();
    }
    return defaultValue;
}

double JsonConfigParser::getDouble(const std::string& key, double defaultValue) const {
    if (root.isMember(key) && root[key].isDouble()) {
        return root[key].asDouble();
    }
    return defaultValue;
}
double JsonConfigParser::getDouble(const std::string& key,const std::string& key2, double defaultValue) const {
    if (root.isMember(key) && root[key].isMember(key2) && root[key][key2].isDouble()) {
        return root[key][key2].asDouble();
    }
    return defaultValue;
}
double JsonConfigParser::getDouble(const std::string& key,const std::string& key2,const std::string& key3, double defaultValue) const {
    if (root.isMember(key) && root[key].isMember(key2) && root[key][key2].isMember(key3) && root[key][key2][key3].isDouble()) {
        return root[key][key2][key3].asDouble();
    }
    return defaultValue;
}

std::string JsonConfigParser::getString(const std::string& key,const std::string& defaultValue) const {
    if (root.isMember(key) && root[key].isString()) {
        return root[key].asString();
    }
    return defaultValue;
}

std::string JsonConfigParser::getString(const std::string& key1,const std::string& key2,const std::string& defaultValue) const {
    if (root.isMember(key1) && root[key1][key2].isString()) {
        return root[key1][key2].asString();
    }
    return defaultValue;
}

std::string JsonConfigParser::getString(const std::string& key1,const std::string& key2,const std::string& key3,const std::string& defaultValue) const {
    if (root.isMember(key1) && root[key1].isMember(key2) && root[key1][key2].isMember(key3) && root[key1][key2][key3].isString()) {
        return root[key1][key2][key3].asString();
    }
    return defaultValue;
}