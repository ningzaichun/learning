# makefile
# 规则之间的嵌套
# 规则1  
# -lpthread 解决下面这个报错问题
#log.o: In function `std::thread::thread<void (&)()>(void (&)())':
#log.cpp:(.text._ZNSt6threadC2IRFvvEJEEEOT_DpOT0_[_ZNSt6threadC5IRFvvEJEEEOT_DpOT0_]+0x2f): undefined reference to `pthread_create'

src=$(wildcard *.cpp)
obj=$(patsubst %.cpp, %.o, $(src))
target=app
$(target):$(obj)
	g++  -std=c++11 $(obj) -lpthread -I/usr/include/jsoncpp -ljsoncpp -o $(target) 
## 自动变量只能在规则的命令中使用
#$@	表示目标文件的名称，包含文件扩展名
#$^	依赖项中，所有不重复的依赖文件，这些文件之间以空格分开
#app:buffer.o log.o main.o
#	g++ $^ -o $@ -lpthread

#buffer.o:buffer.cpp
#	g++ -c buffer.cpp

#log.o:log.cpp
#	g++ -c log.cpp

#main.o:main.cpp
#	g++ -c main.cpp


# 模式匹配 精简代码
%.o:%.cpp
	g++ $< -c -I/usr/include/jsoncpp -ljsoncpp 

# 添加规则, 删除生成文件 *.o 可执行程序
# 声明clean为伪文件
.PHONY:clean
clean:
# shell命令前的 - 表示强制这个指令执行, 如果执行失败也不会终止
	-rm $(obj) $(target) 
	echo "hello, 我是测试字符串"

#第一：makefile的命令行，开头必须用tab键，目前没有发现tabstop的设定值的不同，会引起error。例如:
#set tabstop=3(默认）  OR   set tabstop=4等，均可以。
#第二：编码方式引起的原因。这个原因不多见，不容易发现。查看/etc/vimrc文件以及~/.vimrc，查看是否有set fileencodings的选项，是否设定了utf-8。没有的话加上。
