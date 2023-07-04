#include <iostream>
#include "log.h"

int main() {
    Log::Instance()->init(1, "./log", ".log", 120);
    LOG_INFO("========== Main start ==========");
    LOG_INFO("LogSys level: %d", 2);
    LOG_INFO("SqlConnPool num: %d, ThreadPool num: %d", 10, 2);
    return 0;
}
