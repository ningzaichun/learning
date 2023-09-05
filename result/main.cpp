#include <iostream>
#include "result.h"
#include <vector>
#include <json/json.h>

int main() {
   InferenceResult inferenceResult;
   inferenceResult.sink_topic="123";
   inferenceResult.http_endpoint="123";
   inferenceResult.source_topic="123";
   inferenceResult.timestamp_ms=12333L;
   inferenceResult.result_image="123";
   InferenceResult::InferenceItem inferenceItem;
   inferenceItem.x1=1.1;
   inferenceItem.y1=1.1;
   inferenceItem.x2=1.1;
   inferenceItem.y2=1.1;
   inferenceItem.confidence=1.1;
   inferenceItem.class_id=1;
   inferenceItem.class_name="person";
   std::vector<InferenceResult::InferenceItem> results;
    results.push_back(inferenceItem);
    inferenceResult.results=results;
    std::string test=inferenceResult.toJson();
    std::cout << test<<std::endl;
    return 0;
}
