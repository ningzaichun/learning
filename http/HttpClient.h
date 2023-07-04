#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <vector>

class HttpClient {
public:
    HttpClient(const std::string& baseUrl);
    ~HttpClient();

    std::string sendGetRequest(const std::string& endpoint, const std::string& params);
    std::string sendPostRequest(const std::string& endpoint, const std::string& jsonData);

private:
    std::string baseUrl;
    std::string getHostFromUrl(const std::string& url);
    std::string getPathFromUrl(const std::string& url);
    std::string buildGetRequest(const std::string& host, const std::string& path, const std::string& params);
    std::string buildPostRequest(const std::string& host, const std::string& path, const std::string& jsonData);
    std::string sendHttpRequest(const std::string& request);
    std::vector<std::string> splitString(const std::string& str, char delimiter);
};

#endif // HTTPCLIENT_H
