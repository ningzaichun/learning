#include <iostream>
#include <vector>
#include <string>

class Test {
private:
    std::vector<std::string> class_names;

public:
    // 添加一个公共成员函数（getter）来获取 class_names
    const std::vector<std::string>& getClassNames() const {
        return class_names;
    }

    // 添加一个公共成员函数（setter）来设置 class_names
    void setClassNames(const std::vector<std::string>& names) {
        class_names = names;
    }
};

int main() {
    Test obj;
    obj.setClassNames({"ClassA", "ClassB", "ClassC"});

    // 使用新添加的成员函数来获取 class_names
    const std::vector<std::string>& names = obj.getClassNames();

    // 打印 class_names 的内容
    for (const auto& name : names) {
        std::cout << name << std::endl;
    }

    return 0;
}
