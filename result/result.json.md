```json
{
    "sink_topic": "ai/[应用名]/[算法名]/[边缘设备hostname]/[摄像头唯一标识]",   // mqtt sink topic
    "http_endpoint":"http://192.168.88.150:7890/api/v1/upload",
    "source_topic": "rtsp://admin:123456@192.168.88.161:554/Streams/Channels/101",           // source 视频来源吧
    "timestamp_ms": 1663315677601,// 解码本帧时的时间戳，单位ms
    "results": [    // 推理结果 数据集
        {
            "x1": 0,                          // 左上横坐标，坐标系图像左上角为原点，沿宽向右为横轴，沿高向下为纵轴
            "y1": 269,                        // 左上纵坐标
            "x2": 80.875,                     // 右下横坐标
            "y2": 719,                        // 右下纵坐标
            "confidence": 0.8101108074188232, // 目标置信度
            "class_id": 0,                    // 目标在标签列表对应的序号
            "class_name": "person"            // 目标类别 或者 label 标签
        },
        {
            "x1": 270.875,
            "y1": 371.625,
            "x2": 507.625,
            "y2": 704.375,
            "confidence": 0.7719242572784424,
            "class_id": 0,
            "class_name": "person"
        }
    ],
    "result_image": "/9j/4AAQSkZJRgABA..."    // 图像的base64编码
}
```
测试代码
```c++
#include <iostream>

int main() {
    InferenceResult result;
    // 假设你已经从JSON中解析并填充了result对象
    std::cout << "Sink Topic: " << result.sink_topic << std::endl;
    std::cout << "HTTP Endpoint: " << result.http_endpoint << std::endl;
    std::cout << "Source Topic: " << result.source_topic << std::endl;
    std::cout << "Timestamp (ms): " << result.timestamp_ms << std::endl;

    std::cout << "Inference Results:" << std::endl;
    for (const auto& item : result.results) {
        std::cout << "x1: " << item.x1 << ", y1: " << item.y1 << ", x2: " << item.x2 << ", y2: " << item.y2 << std::endl;
        std::cout << "Confidence: " << item.confidence << ", Class ID: " << item.class_id << ", Class Name: " << item.class_name << std::endl;
    }

    std::cout << "Result Image: " << result.result_image << std::endl;
    return 0;
}
```
