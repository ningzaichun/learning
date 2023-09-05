#include "FolderHandler.h"
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
#include <pwd.h>

FolderHandler::FolderHandler(const std::string& folderPath)
    : folderPath(folderPath) {}

FolderHandler::~FolderHandler() {}

std::string FolderHandler::get_home_directory()
{
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == nullptr) {
        std::cerr << "Failed to get user information" << std::endl;
        return "";
    }
    return pw->pw_dir;
}

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
