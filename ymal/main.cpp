#include "config.h"
int main() {
    ConfigParser config("config.yaml");
    // config.parse();
    if(config.parse()){
        ModelConfig modelConfig_=config.getModelConfig();
        std::cout <<modelConfig_.name <<std::endl;
        std::cout <<modelConfig_.source_type <<std::endl;
        std::cout <<modelConfig_.decoder_out_width <<std::endl;
        std::cout <<modelConfig_.decoder_out_height <<std::endl;
        std::cout <<modelConfig_.algorithm <<std::endl;
        std::cout <<modelConfig_.model_type <<std::endl;
        std::cout <<modelConfig_.model_in_path <<std::endl;
        std::cout <<modelConfig_.sink_type <<std::endl;

        std::cout <<modelConfig_.rtsp_source_config.rtsp_source_uris <<std::endl;
        std::cout <<modelConfig_.mqtt_sink_config.sink_ip <<std::endl;
        std::cout <<modelConfig_.mqtt_sink_config.sink_port <<std::endl;
        std::cout <<modelConfig_.mqtt_sink_config.sink_original_img <<std::endl;
        std::cout <<modelConfig_.mqtt_sink_config.mqtt_qos <<std::endl;
        std::cout <<modelConfig_.http_sink_config.http_sink_uri <<std::endl;
    }else{
        std::cerr<<"parse config.yaml errer"<<std::endl;
        return 1;
    }

    return 0;
}
