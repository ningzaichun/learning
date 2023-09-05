#include "HttpClient.h"



// HttpClient::HttpClient(const std::string& baseUrl)
//     : baseUrl(baseUrl) {}

HttpClient::HttpClient(const std::string& baseUrl) {
      

}
HttpClient::~HttpClient() {}

std::vector<std::string> HttpClient::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string HttpClient::getHostFromUrl(const std::string& url) {
    size_t start = url.find("://");
    if (start != std::string::npos) {
        start += 3;
        size_t end = url.find('/', start);
        if (end != std::string::npos) {
            return url.substr(start, end - start);
        }
    }
    return "";
}

std::string HttpClient::getPathFromUrl(const std::string& url) {
    size_t start = url.find("://");
    if (start != std::string::npos) {
        start += 3;
        size_t end = url.find('/', start);
        if (end != std::string::npos) {
            return url.substr(end);
        }
    }
    return "/";
}

std::string HttpClient::buildGetRequest(const std::string& host, const std::string& path, const std::string& params) {
    std::string request = "GET " + path + "?" + params + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "Connection: close\r\n";
    request += "\r\n";
    return request;
}

std::string HttpClient::buildPostRequest(const std::string& host, const std::string& path, const std::string& jsonData) {
    std::string request = "POST " + path + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "Content-Type: application/json\r\n";
    request += "Content-Length: " + std::to_string(jsonData.size()) + "\r\n";
    request += "Connection: close\r\n";
    request += "\r\n";
    request += jsonData;
    return request;
}

std::string HttpClient::sendHttpRequest(const std::string& request) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return "";
    }

    std::string host = getHostFromUrl(baseUrl);
    std::vector<std::string> parts = splitString(host, ':');
    std::string ipAddress = parts[0];
    std::string port = parts[1];

    // 2. 连接服务器
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(std::stoi(port));   // 大端端口
    inet_pton(AF_INET, ipAddress.c_str(), &addr.sin_addr.s_addr);
    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        std::cerr << "Failed to connect to server" << std::endl;
        close(sockfd);
        return "";
    }

    if (send(sockfd, request.c_str(), request.length(), 0) == -1) {
        std::cerr << "Failed to send request" << std::endl;
        close(sockfd);
        return "";
    }

    std::string response;
    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
        response.append(buffer, bytesRead);
    }
    close(sockfd);
    return response;
}

std::string HttpClient::sendGetRequest(const std::string& endpoint, const std::string& params) {
    std::string host = getHostFromUrl(baseUrl);
    std::string path = getPathFromUrl(baseUrl + endpoint);
    std::string request = buildGetRequest(host, path, params);
    return sendHttpRequest(request);
}
std::string HttpClient::sendPostRequest(const std::string& endpoint, const std::string& jsonData) {
    std::string host = getHostFromUrl(baseUrl);
    std::string path = getPathFromUrl(baseUrl + endpoint);
    std::string request = buildPostRequest(host, path, jsonData);

    std::cout<<"host:>>>"<<host<<std::endl;
    std::cout<<"path:>>>"<<path<<std::endl;
    std::cout<<"request:>>>"<<request<<std::endl;
    return sendHttpRequest(request);
}