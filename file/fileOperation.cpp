/*==========================================================================
使用 mkdir 逐层创建文件夹
============================================================================*/

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <chrono> // 关于时间的请求头
#include <thread>


static std::string getCurrentDate() {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);

    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << (timeinfo->tm_year + 1900)
        << std::setw(2) << std::setfill('0') << (timeinfo->tm_mon + 1)
        << std::setw(2) << std::setfill('0') << timeinfo->tm_mday;

    return oss.str();
}

static bool createDirectory(const std::string& path) {
    int result = mkdir(path.c_str(), 0755);
    if (result == 0) {
        std::cout << "Directory created: " << path << std::endl;
        return true;
    } else if (errno == EEXIST) {
        std::cout << "Directory already exists: " << path << std::endl;
        return true;
    } else {
        std::cerr << "Failed to create directory: " << path << std::endl;
        return false;
    }
}


int main(int argc, char *argv[]){
    std::string currentDate = getCurrentDate();
    createDirectory("/home/linaro/demo4/yolov5_out_img");
    std::string directoryPath = "/home/linaro/demo4/yolov5_out_img/" + currentDate+"/";
    createDirectory(directoryPath);
}
