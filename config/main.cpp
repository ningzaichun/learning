#include <iostream>
#include "ConfigParser.h"
#include <vector>

static std::string trim(std::string &s) {  
  if (s.empty()){  
    return s;  
  }  
  s.erase(0,s.find_first_not_of(" "));  
  s.erase(s.find_last_not_of(" ") + 1);  
  return s;  
}
static std::vector<std::string> split(const std::string& s){
  std::vector<std::string> result(1);
  for(auto c: s){
    if(c==','){
      result.back() = trim(result.back());
      result.push_back("");
    } else {
      result.back() += c;
    }
  }
  result.back() = trim(result.back());
  return result;
}

int main() {
    ConfigParser config("config.json");
    if (!config.loadConfig()) {
        std::cerr << "Load to JSON file error.\n";
        return 1;
    }

    ModelConfig modelConfig=config.getModelConfig();
    // Print the parsed values
    std::cout << "Name: " << modelConfig.name << std::endl;
    std::cout << "input url: " << modelConfig.rtsp_source_config.rtsp_source_uris << std::endl;

    auto inputs=split(modelConfig.rtsp_source_config.rtsp_source_uris);
    for(auto image_file:inputs){
        std::cout<<"image_file:"<<image_file<<std::endl;
    }
    std::cout << "Source Type: " << modelConfig.source_type << std::endl;
    std::cout << "Decoder Output Width: " << modelConfig.decoder_out_width << std::endl;
    std::cout << "Decoder Output Height: " << modelConfig.decoder_out_height << std::endl;
    std::cout << "IsVideo: " << modelConfig.is_video << std::endl;
    std::cout << "Algorithm: " << modelConfig.algorithm << std::endl;
    std::cout << "Model Type: " << modelConfig.model_type << std::endl;
    std::cout << "Model Input Path: " << modelConfig.model_in_path << std::endl;
    // std::cout << "Class Input Path: " << modelConfig.class_names << std::endl;
   std::cout << "Class Names: ";
    for (const auto &className : modelConfig.class_names) {
        std::cout << className << " ";
    }
    std::cout << std::endl;

    std::cout << "sink_type Input Path: " << modelConfig.sink_type << std::endl;
}