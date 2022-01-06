# cmake参数解析:
```
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")
```

CXXFLAGS: 环境变量

-rdynamic: 连接选项，它将指示连接器把所有符号（而不仅仅只是程序已使用到的外部符号）都添加到动态符号表（即.dynsym表）里，以便那些通过dlopen()或backtrace()（这一系列函数使用.dynsym表内符号）这样的函数使用

-O0:

-O/O1: 这两个命令的效果是一样的，目的都是在不影响编译速度的前提下，尽量采用一些优化算法降低代码大小和可执行代码的运行速度

-O2: 该优化选项会牺牲部分编译速度，除了执行-O1所执行的所有优化之外，还会采用几乎所有的目标配置支持的优化算法，用以提高目标代码的运行速度

-O3: 该选项除了执行-O2所有的优化选项之外，一般都是采取很多向量化算法，提高代码的并行执行程度，利用现代CPU中的流水线，Cache等

-g: 调试选项，因此在一般需要进行程序调试的场景下，我们都会加上该选项，并且根据调试工具的不同，还能直接选择更有针对性的说明，比如 -ggdb 。-g是一个编译选项，即在源代码编译的过程中起作用，让gcc把更多调试信息（也就包括符号信息）收集起来并将存放到最终的可执行文件内

-std=c++11: 就是用按C++2011标准来编译的

-Wall: 生成所有警告信息

-Wno-deprecated: 告诉编译器 g++ 使用 C++ 标准废弃的特性不告警

-Werror: 它要求GCC将所有的警告当成错误进行处理

-Wno-unused-function: 不警告声明但是没有定义的static函数;


```
include_directories(.)
include_directories(/apps/sylar/include)
```
include_directories ([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])

将指定目录添加到编译器的头文件搜索路径之下，指定的目录被解释成当前源码路径的相对路径。

# Linux下指定编译器

export CC=/usr/local/bin/gcc  //安装的gcc目录

export CXX=/usr/local/bin/g++ //安装的g++目录

cmake ..

make

# CMake 安装软件指定安装目录方法

方法1：

命令

cmake -DCMAKE_INSTALL_PREFIX=/usr ..

方法二：

修改cmake文件，加入：

SET(CMAKE_INSTALL_PREFIX <install_path >)

要加在 PROJECT(< project_name>) 之后

参考: https://www.cnblogs.com/fengbeihong/p/3641384.html