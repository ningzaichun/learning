/**
最简单的web服务
编译链接之后，启动可执行文件，然后在浏览器输入 
get方法:   就是在浏览器中输入 localhost:8080  就会返回一段简单的文本
post方法，使用 post 请求即可，使用 curl 或者是 postman 进行测试


**/

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

const int PORT = 8080;

void handle_get(int clientSocket)
{
    std::string response = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/plain\r\n"
                           "\r\n"
                           "This is a GET request";

    send(clientSocket, response.c_str(), response.length(), 0);
}

void handle_post(int clientSocket, const std::string& requestBody)
{
    std::string response = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/plain\r\n"
                           "\r\n"
                           "This is a POST request\n"
                           "Request Body: " + requestBody;

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

    if (request.find("GET") == 0) {
        handle_get(clientSocket);
    } else if (request.find("POST") == 0) {
        std::string requestBody;
        size_t pos = request.find("\r\n\r\n");
        if (pos != std::string::npos)
            requestBody = request.substr(pos + 4);

        handle_post(clientSocket, requestBody);
    }

    close(clientSocket);
}

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
