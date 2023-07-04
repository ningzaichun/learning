#include "FolderHandler.h"
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>

FolderHandler::FolderHandler(const std::string& folderPath)
    : folderPath(folderPath) {}

FolderHandler::~FolderHandler() {}

bool FolderHandler::createFolder() {
    if (folderExists()) {
        return true;  // Folder already exists
    }

    int status = mkdir(folderPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (status == 0) {
        return true;
    } else {
        return false;
    }
}

bool FolderHandler::deleteFolder() {
    if (!folderExists()) {
        return true;  // Folder doesn't exist
    }

    std::string command = "rm -r " + folderPath;
    int status = system(command.c_str());

    if (status == 0) {
        return true;
    } else {
        return false;
    }
}

bool FolderHandler::folderExists() {
    struct stat buffer;
    return (stat(folderPath.c_str(), &buffer) == 0);
}

bool FolderHandler::createNestedFolders() {
    if (folderExists()) {
        return true;  // Folder already exists
    }

    std::string command = "mkdir -p " + folderPath;
    int status = system(command.c_str());

    if (status == 0) {
        return true;
    } else {
        return false;
    }
}

bool FolderHandler::createDatedFolder() {
    if (!folderExists()) {
        std::cout << " Folder already no exists!" << std::endl;
        return false;  // 
    }
    time_t now = time(0);
    struct tm* timeinfo;
    char dateStr[11];
    timeinfo = localtime(&now);
    strftime(dateStr, sizeof(dateStr), "%Y/%m/%d", timeinfo);
    std::string folderPathWithDate = folderPath + "/" + dateStr;

    std::string command = "mkdir -p " + folderPathWithDate;

    std::cout<<command<<std::endl;
    int status = system(command.c_str());

    if (status == 0) {
        return true;
    } else {
        return false;
    }
}
