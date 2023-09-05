# makefile
# 规则之间的嵌套
# 规则1
app:FolderHandler.o main.o 
	g++ FolderHandler.o main.o -o app
# 规则2
FolderHandler.o:FolderHandler.cpp
	g++ -c FolderHandler.cpp
# 规则3
main.o:main.cpp
	g++ -c main.cpp

#第一：makefile的命令行，开头必须用tab键，目前没有发现tabstop的设定值的不同，会引起error。例如:
#set tabstop=3(默认）  OR   set tabstop=4等，均可以。
#第二：编码方式引起的原因。这个原因不多见，不容易发现。查看/etc/vimrc文件以及~/.vimrc，查看是否有set fileencodings的选项，是否设定了utf-8。没有的话加上。
