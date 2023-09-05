#include <iostream>
#include <vector>

static std::string trim(std::string &s) {  
  if (s.empty()){  
    return s;  
  }  
  s.erase(0,s.find_first_not_of(" "));  
  s.erase(s.find_last_not_of(" ") + 1);  
  return s;  
}
static std::vector<std::string> split(const std::string& s){
  std::vector<std::string> result(1);
  for(auto c: s){
    if(c==','){
      result.back() = trim(result.back());
      result.push_back("");
    } else {
      result.back() += c;
    }
  }
  result.back() = trim(result.back());
  return result;
}

int main(){
    std::string str="1.jpeg,2.jpeg";
    auto inputs=split(str);
    for(auto image_file:inputs){
        std::cout<<"image_file:"<<image_file<<std::endl;
    }
    return 0;
}