#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

std::string urlEncode(const std::string& value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : value) {
        // 保留安全字符和部分特殊字符
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        }
        else {
            // 转义非安全字符为%XX形式
            escaped << std::uppercase;
            escaped << '%' << std::setw(2) << int(static_cast<unsigned char>(c));
            escaped << std::nouppercase;
        }
    }

    return escaped.str();
}

int main() {
    std::string url = "https://example.com/api?param=";

    // 假设参数中有中文字符
    std::string chineseParam = "中文";

    // 对中文参数进行编码
    std::string encodedParam = urlEncode(chineseParam);

    // 拼接编码后的参数到URL中
    url += encodedParam;

    std::cout << "Encoded URL: " << url << std::endl;

    // 发送GET请求...
    // 请使用你偏好的库或方法来发送GET请求

    return 0;
}
