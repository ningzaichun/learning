#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <unordered_map>

const int PORT = 8080;

std::unordered_map<std::string, std::string> parse_query_string(const std::string& query_string)
{
    std::unordered_map<std::string, std::string> params;

    std::string::size_type pos = 0;
    while (pos < query_string.length()) {
        std::string::size_type end = query_string.find('&', pos);
        std::string::size_type eq = query_string.find('=', pos);

        if (end == std::string::npos)
            end = query_string.length();

        if (eq != std::string::npos && eq < end)
            params[query_string.substr(pos, eq - pos)] = query_string.substr(eq + 1, end - eq - 1);

        pos = end + 1;
    }

    return params;
}

void handle_get(int clientSocket, const std::string& query_string)
{
    std::unordered_map<std::string, std::string> params = parse_query_string(query_string);

    std::string response = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/plain\r\n"
                           "\r\n"
                           "This is a GET request\n"
                           "Parameters:\n";

    for (const auto& param : params) {
        response += param.first + " = " + param.second + "\n";
    }

    send(clientSocket, response.c_str(), response.length(), 0);
}

void handle_post(int clientSocket, const std::string& requestBody)
{
    std::unordered_map<std::string, std::string> params = parse_query_string(requestBody);

    std::string response = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/plain\r\n"
                           "\r\n"
                           "This is a POST request\n"
                           "Parameters:\n";

    for (const auto& param : params) {
        response += param.first + " = " + param.second + "\n";
    }

    send(clientSocket, response.c_str(), response.length(), 0);
}

void handle_request(int clientSocket)
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        close(clientSocket);
        return;
    }
    std::string request(buffer);
    std::string::size_type pos = request.find(' ');
    if (pos == std::string::npos) {
        close(clientSocket);
        return;
    }
    std::string method = request.substr(0, pos);
    std::string::size_type end = request.find(' ', pos + 1);
    if (end == std::string::npos) {
        close(clientSocket);
        return;
    }
    std::string path = request.substr(pos + 1, end - pos - 1);




    std::string::size_type queryPos = path.find('?');
    std::string query_string;
    if (queryPos != std::string::npos) {
        query_string = path.substr(queryPos + 1);
        path = path.substr(0, queryPos);
    }
    if (method == "GET") {
        handle_get(clientSocket, query_string);
    } else if (method == "POST") {
        std::string requestBody;
        std::string::size_type pos = request.find("\r\n\r\n");
    if (pos != std::string::npos)
        requestBody = request.substr(pos + 4);
        handle_post(clientSocket, requestBody);
    }

    close(clientSocket);
}
//http://192.168.79.137:8080/data?key1=value1&key2=value2
int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create server socket" << std::endl;
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind to port " << PORT << std::endl;
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Failed to listen on port " << PORT << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Web service is listening on port " << PORT << std::endl;

    while (true) {
        sockaddr_in clientAddress{};
        socklen_t clientAddressSize = sizeof(clientAddress);

        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
        if (clientSocket == -1) {
            std::cerr << "Failed to accept client connection" << std::endl;
            continue;
        }
        handle_request(clientSocket);
    }

   close(serverSocket);

    return 0;
}