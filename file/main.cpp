#include "FolderHandler.h"
#include <iostream>

int main() {
    std::string folderPath = "/home/ym/cpp_demo/";

    FolderHandler folder(folderPath);

    if (folder.createDatedFolder()) {
        std::cout << "Dated folder created successfully!" << std::endl;
    } else {
        std::cout << "Failed to create dated folder"<<std::endl;
    }
    return 0;
}
// g++ -c FolderHandler.cpp
// g++ main.cpp -o test FolderHandler.o 
// ./test

// or 
// g++ -c FolderHandler.cpp 
// g++ -c main.cpp 
// g++ FolderHandler.o main.o -o test
