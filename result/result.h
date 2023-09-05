#ifndef RESULT_H
#define RESULT_H
#include <string>
#include <vector>
#include <json/json.h>

class InferenceResult {
public:
    struct InferenceItem {
        double x1;
        double y1;
        double x2;
        double y2;
        double confidence; // 置信度
        int class_id;      // 类别ID
        std::string class_name; //类别名
    };

    std::string sink_topic; // MQTT 时，发送的主题名
    std::string http_endpoint; // http 端点
    std::string source_topic;   // 视频来源 
    long long timestamp_ms;     // 时间戳
    std::vector<InferenceItem> results; // 推理结果集 每个框的位置、类别、置信度等
    std::string result_image;    // 图片的base64编码

    InferenceResult() = default;
    ~InferenceResult() = default;

    // 将类数据转换为JSON格式
    std::string toJson() const {
        Json::Value jsonData;
        jsonData["sink_topic"] = sink_topic;
        jsonData["http_endpoint"] = http_endpoint;
        jsonData["source_topic"] = source_topic;
        jsonData["timestamp_ms"] = Json::Value::Int64(timestamp_ms);
        jsonData["result_image"] = result_image;

        for (const auto& item : results) {
            Json::Value result_item;
            result_item["x1"] = item.x1;
            result_item["y1"] = item.y1;
            result_item["x2"] = item.x2;
            result_item["y2"] = item.y2;
            result_item["confidence"] = item.confidence;
            result_item["class_id"] = item.class_id;
            result_item["class_name"] = item.class_name;
            jsonData["results"].append(result_item);
        }
        Json::StreamWriterBuilder writer;
        return Json::writeString(writer, jsonData);
    }

};

#endif // RESULT_H
