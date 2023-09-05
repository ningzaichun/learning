#include <iostream>


std::string buildDatedStr() {
    time_t now = time(0);
    struct tm* timeinfo;
    char dateStr[11];
    timeinfo = localtime(&now);
    strftime(dateStr, sizeof(dateStr), "%Y/%m/%d", timeinfo);
    return dateStr;
}


int main() {
    buildDatedStr();
    return 0;
}
