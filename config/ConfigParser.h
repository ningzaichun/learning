#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <nlohmann/json.hpp>
#include "modelConfig.h"
class ConfigParser {
public:
    ConfigParser(const std::string& filename);

    bool loadConfig();
    const ModelConfig& getModelConfig() const;

    std::string getName() const;
    std::string getSourceType() const;
    int getDecoderOutWidth() const;
    int getDecoderOutHeight() const;
    bool getIsVideo() const;
    std::string getRTSPSourceURIs() const;
    std::string getAlgorithm() const;
    std::string getModelType() const;
    std::string getModelInPath() const;
    std::vector<std::string> getClassNames() const;
    std::string getSinkType() const;
    std::string getSinkIP() const;
    int getSinkPort() const;
    bool getSinkOriginalImg() const;
    int getMQTTQoS() const;
    std::string getHttpSinkURI() const;
    std::string getHttpSinkEndpoint() const;

private:
    std::string filename;
    nlohmann::json jsonData;
    ModelConfig modelConfig_;
    bool parse();
};

#endif // CONFIG_PARSER_H
