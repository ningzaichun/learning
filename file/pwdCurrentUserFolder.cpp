#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

std::string get_home_directory()
{
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == nullptr) {
        std::cerr << "Failed to get user information" << std::endl;
        return "";
    }
    return pw->pw_dir;
}

int main()
{
    std::string homeDir = get_home_directory();
    if (!homeDir.empty()) {
        std::cout << "Home directory: " << homeDir << std::endl;
    }

    return 0;
}
