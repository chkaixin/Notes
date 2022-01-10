# gdb gcc

## gcc常用指令

在 深入了解C++ 系列中，我经常使用如下的格式进行编译、执行demo：

$ g++ -g -O0 main.cc -o main && ./main

下面，我们来看看常用的gcc编译选项有哪些。
```
选项	作用
-E	生成预处理文件
-S	生成汇编文件
-c	生成可目标文件
-o	指定生成文件的文件名
-On	指定代码优化等级
-g	用于gdb调试、objdump
-Wall	显示代码中的所有warning行为
-w	禁止显示代码中的warning行为
-Werror	将代码中的warning行为视为为error
-D	设置预定义宏
-l	链接（link）指定的函数库
-std=c++11	指定编译代码的C++标准为C++11
对于这些编译选项中的个别，简单的解释下。
```
-E、  -S  、-c 三个选项直接对应着编译的前三个基本阶段。

预编译处理(.i)

将源文件main.cc 经过预处理后，生成文件预处理所得文件main.i

g++ -E main.cc -o main.i

编译、优化程序（.s）

将 main.i 文件翻译成一个汇编文件 main.s

g++ -S main.i  -o main.s

汇编程序(.o)

运行汇编器，将 main.s 翻译成一个可重定位目标文件 main.o   ；

g++ -c main.s -o main.o

链接程序（.elf）

运行链接器，将 main.o 中使用到的目标文件组合起来，并创建一个可执行的文件 main  。由于main.cc代码没有额外的依赖，因此可以直接输出main文件。

g++ main.o -o main

实际上，一步就能完成上面所有的操作：

g++ main.cc -o main

定义宏 -D

比如，对于下面的一段demo，如果定义了宏DEBUG，则输出hello cpp。

```c++
int main(int argc, char const *argv[]) {
#ifdef DEBUG
  std::cout<<"Hello Cpp" <<std::endl;
#endif
  return 0;
}
```

下面在gcc编译时基于-D选项设置DEBUG宏，来控制程序执行。

$ g++ -DDEBUG main.cc -o main && ./main

Hello Cpp

对于GCC的编译选项，没有必要全部记住，记住常用的即可，其他用到了再去官网查询：

https://gcc.gnu.org/onlinedocs/gcc/Invoking-GCC.html

## 编译选项

-Wall			// 大部分警告 

-Wextra			// 一些额外的警告

-Werror			// 当出现警告时转为错误，停止编译

-Wconversion		// 一些可能改变值的隐式转换，给出警告。

-Wno-unused-parameter	// 函数中出现未使用的参数，不给出警告。

-Wold-style-cast		// C风格的转换，给出警告

-Woverloaded-virtual	// 如果函数的声明隐藏住了基类的虚函数，就给出警告。

-Wpointer-arith		// 对函数指针或者void *类型的指针进行算术操作时给出警告

-Wshadow		// 当一个局部变量遮盖住了另一个局部变量，或者全局变量时，给出警告。


-Wwrite-strings		// 规定字符串常量的类型是const char[length],因此,把这样的地址复制给 non-const char *指针将产生警告.这些警告能够帮助你在编译期间发现企图写入字符串常量 的代码

-march=native		// 指定cpu体系结构为本地平台

