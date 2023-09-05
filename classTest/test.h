#ifndef TEST_H
#define TEST_H
#include<vector>
#include<string>

class Test{
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

}
#endif // TEST_H