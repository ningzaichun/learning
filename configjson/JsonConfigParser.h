#ifndef JSON_CONFIG_PARSER_H
#define JSON_CONFIG_PARSER_H

#include <json/json.h>
#include <string>
#include "modelConfig.h"

class JsonConfigParser {
public:
    JsonConfigParser();
    
    bool loadConfig(const std::string& filename);
    const ModelConfig& getModelConfig() const;

    int getInt(const std::string& key, int defaultValue = 0) const;
    int getInt(const std::string& key1,const std::string& key2,int defaultValue) const;
    int getInt(const std::string& key1,const std::string& key2,const std::string& key3,int defaultValue) const;
    double getDouble(const std::string& key, double defaultValue = 0.0) const;
    double getDouble(const std::string& key,const std::string& key2, double defaultValue) const;
    double getDouble(const std::string& key,const std::string& key2,const std::string& key3, double defaultValue) const;
    std::string getString(const std::string& key,const std::string& defaultValue="") const;
    std::string getString(const std::string& key1,const std::string& key2,const std::string& defaultValue) const;
    std::string getString(const std::string& key1,const std::string& key2,const std::string& key3,const std::string& defaultValue) const;

private:
    Json::Value root;
    ModelConfig modelConfig_;
    bool parse();
};

#endif // JSON_CONFIG_PARSER_H
