#ifndef MODEL_CONFIG_H
#define MODEL_CONFIG_H

#include <string>

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
    std::string http_sink_endpoint;
};

class ModelConfig {
public:
    std::string name;
    std::string source_type;
    int decoder_out_width;
    int decoder_out_height;
    bool is_video;
    RtspSourceConfig rtsp_source_config;
    std::string algorithm;
    std::string model_type;
    std::string model_in_path;
    std::vector<std::string> class_names;
    std::string sink_type;
    MqttSinkConfig mqtt_sink_config;
    HttpSinkConfig http_sink_config;
};

#endif // JSON_CONFIG_PARSER_H
