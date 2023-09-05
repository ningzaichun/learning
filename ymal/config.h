#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>
#include <fstream>

struct RtspSourceConfig {
    std::string rtsp_source_uris;
    // Add any fields you need to parse for RTSP source configuration
};

struct MqttSinkConfig {
    std::string sink_ip;
    int sink_port;
    bool sink_original_img;
    int mqtt_qos;
    // Add any fields you need to parse for MQTT sink configuration
};

struct HttpSinkConfig {
    // Add any fields you need to parse for HTTP sink configuration
    std::string http_sink_uri;
};

class ModelConfig {
public:
    std::string name;
    std::string source_type;
    int decoder_out_width;
    int decoder_out_height;
    RtspSourceConfig rtsp_source_config;
    std::string algorithm;
    std::string model_type;
    std::string model_in_path;
    std::string sink_type;
    MqttSinkConfig mqtt_sink_config;
    HttpSinkConfig http_sink_config;
};

class ConfigParser {
public:
    ConfigParser(const std::string& filename);

    bool parse();

    const ModelConfig& getModelConfig() const;

private:
    std::string filename_;
    ModelConfig modelConfig_;

    bool parseRtspSource(const YAML::Node& sourceNode, RtspSourceConfig& rtspConfig,const std::string& source_type);

    bool parseMqttSink(const YAML::Node& sinkNode, MqttSinkConfig& mqttConfig,const std::string& sink_type);
    bool parseHttpSink(const YAML::Node& sinkNode, HttpSinkConfig& httpConfig,const std::string& sink_type);
};

#endif // CONFIG_H
