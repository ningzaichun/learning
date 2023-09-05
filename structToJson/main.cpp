#include <iostream>
#include <string>
#include <json/json.h>

// 假设你有以下结构体
struct Person {
    std::string name;
    int age;
    std::string address;
};

// 将结构体转换为 JSON
Json::Value personToJson(const Person& person) {
    Json::Value root;
    root["name"] = person.name;
    root["age"] = person.age;
    root["address"] = person.address;
    return root;
}

int main() {
    // 创建一个结构体对象
    Person person;
    person.name = "John";
    person.age = 30;
    person.address = "123 Main St";

    // 将结构体转换为 JSON
    Json::Value jsonPerson = personToJson(person);

    // 输出 JSON
    Json::StreamWriterBuilder writer;
    std::string jsonString = Json::writeString(writer, jsonPerson);
    std::cout << jsonString << std::endl;

    return 0;
}
