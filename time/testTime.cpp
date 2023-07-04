#include <iostream>
#include <chrono>
#include <thread>

// 定义全局变量来保存上一次发送请求的时间戳
std::chrono::steady_clock::time_point lastRequestTime;

// 发送GET请求的函数
void sendGetRequest() {
    // 在这里编写发送GET请求的代码
    std::cout << "Sending GET request..." << std::endl;
    
    // 更新上一次发送请求的时间戳为当前时间
    lastRequestTime = std::chrono::steady_clock::now();
}

int main() {
    // 初始化上一次发送请求的时间戳为当前时间的前五分钟
    lastRequestTime = std::chrono::steady_clock::now() - std::chrono::minutes(5);
    
    while (true) {
        // 获取当前时间
        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        
        // 计算当前时间与上一次发送请求时间戳的差值
        std::chrono::steady_clock::duration elapsedDuration = currentTime - lastRequestTime;
        
        // 将差值转换为分钟
        int elapsedMinutes = std::chrono::duration_cast<std::chrono::minutes>(elapsedDuration).count();
        
        if (elapsedMinutes >= 5) {
            // 超过了五分钟的限制时间，可以发送请求
            sendGetRequest();
        } else {
            // 还未到五分钟的限制时间，等待一段时间再检查
            int remainingMinutes = 5 - elapsedMinutes;
            std::cout << "Waiting for " << remainingMinutes << " minutes..." << std::endl;
            
            // 等待 remainingMinutes 分钟
            std::this_thread::sleep_for(std::chrono::minutes(remainingMinutes));
        }
    }
    
    return 0;
}
