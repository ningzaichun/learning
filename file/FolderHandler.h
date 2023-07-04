#ifndef FOLDERHANDLER_H
#define FOLDERHANDLER_H

#include <string>

class FolderHandler {
public:
    FolderHandler(const std::string& folderPath);
    ~FolderHandler();

    bool createFolder();
    bool deleteFolder();
    bool folderExists();
    bool createNestedFolders();
    bool createDatedFolder();

private:
    std::string folderPath;
    bool createFolderRecursive(const std::string& path);
};

#endif // FOLDERHANDLER_H
