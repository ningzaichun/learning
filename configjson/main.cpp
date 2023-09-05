#include <iostream>
#include "JsonConfigParser.h"

int main() {
    JsonConfigParser configParser;
    if (configParser.loadConfig("config.json")) {
        ModelConfig modelConfig=configParser.getModelConfig();
        std::cout<<modelConfig.name<<std::endl;
        std::cout<<modelConfig.source_type<<std::endl;
        std::cout<<modelConfig.decoder_out_width<<std::endl;
        std::cout<<modelConfig.decoder_out_height<<std::endl;
        std::cout<<modelConfig.algorithm<<std::endl;
        std::cout<<modelConfig.model_type<<std::endl;
        std::cout<<modelConfig.model_in_path<<std::endl;
        std::cout<<modelConfig.class_in_path<<std::endl;
        std::cout<<modelConfig.sink_type<<std::endl;
    }

    return 0;
}
