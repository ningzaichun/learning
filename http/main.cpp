#include <iostream>
#include "HttpClient.h"

int main() {
    std::string baseUrl = "http://192.168.1.107:8089/";
    HttpClient client(baseUrl);

    // Send a GET request with parameters
    std::string endpoint = "data";
    std::string params = "param1=value1&param2=value2";
    std::string response = client.sendGetRequest(endpoint, params);
    std::cout << "GET Response: " << response << std::endl;

    // Send a POST request with JSON data
    std::string jsonData = "{\"key1\": \"value1\", \"key2\": \"value2\"}";
    std::string postResponse = client.sendPostRequest(endpoint, jsonData);
    std::cout << "POST Response: " << postResponse << std::endl;

    return 0;
}
