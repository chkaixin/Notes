# gdb常用指令

官方网站详细介绍:
https://sourceware.org/gdb/current/onlinedocs/gdb/

## list

list命令可以查看源码。启动GDB后第一个list命令会定位到main函数，以main函数为中心显示上下共10行代码。

下一个list命令查看下面的10行。可以重复执行这个命令，直到到达文件尾。

list -查看前10行代码。

list n命令显示以第n行为中心的上下共10行代码。

list n,命令显示以第n行开头的10行代码。

list ,n显示以第n行结尾的10行代码。

list m,n显示以第m行开头，第n行结尾的代码。

list f以函数f为中心的上下10行代码。f可以是其它文件里定义的函数。

list file:line显示文件file里的第line行代码。

list file:f显示文件file里的函数f的代码。

函数名、文件名＋行号／函数名也都适用于list f1,f2的格式。

## 

关于启动gdb的方式，下面介绍下常用的三种启动gdb方式：

gdb [program]：这种方式最常用，比如使用gdb调试上面编译生成的main文件，那么就直接 gdb main。
gdb [program] core：用于调试导致coredump的错误，此时需要在program后面加上因为coredump生成的core文件路径。
gdb -p [pid]：使用gdb调试正在运行的pid进程
gdb program

以如下的main程序为例：
```c++
// main.cc
#include <iostream>

int main(int argc, char const *argv[])
{
  int cnt =0;
  for(int idx=0; idx < 10; ++idx) { 
    cnt++;
  }
  std::cout<<cnt<<std::endl;

  return 0;
}
```
编译指令：
```
$ g++ -g -O0 main.cc -o main
在终端输入gdb main，会从main文件中加载符号表，便于设置断点等信息：

$ gdb main
GNU gdb (Ubuntu 9.2-0ubuntu1~20.04) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
```
# 以上都是关于gdb的开源信息，为便于描述，下面的教程中会省略这部分信息
```
Reading symbols from main...
(gdb) 
输入gdb main后，会首先显示关于gdb的一大串的开源信息，而且每次启动都会显示。因此，在后文的讲解中，每次启动gdb会省略掉这部分信息。
```
attach pid

如果某个程序正在运行出现故障，比如服务器程序，无法被中止，如何使用gdb来调试它？

比如，此刻我电脑正在运行REDIS服务器程序，其pid是1607：

我先以root权限启动gdb
再使用attach pid命令来调试正在运行的REDIS服务器程序
示例如下：
```
$ sudo gdb       # 先以root权限启动gdb
# ...关于gdb的开源声明省略
(gdb) attach 1607     # 再使当前gdb环境去调试redis服务器
Attaching to process 1607
[New LWP 1608]
[New LWP 1609]
[New LWP 1610]
[New LWP 1611]
[New LWP 1612]
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
0x00007f2d694925ce in epoll_wait (epfd=5, events=0x7f2d68ede980, maxevents=10128, timeout=100)
    at ../sysdeps/unix/sysv/linux/epoll_wait.c:30
30      in ../sysdeps/unix/sysv/linux/epoll_wait.c
(gdb) 
当使用attach命令调试完服务器程序，可以使用detach指令退出。

(gdb) detach   
Detaching from program: /home/szza/redis-6.0.5/redis-6.0.5/src/redis-server, process 1607
[Inferior 1 (process 1607) detached]
gdb -p pid
```
当然，也可以直接使用gdb -p pid指令，来调试正在运行的REDIS服务器程序，其效果和attach一致：
```
$ sudo gdb -p 1607    # 也要使用root权限
Attaching to process 1607
[New LWP 1608]
[New LWP 1609]
[New LWP 1610]
[New LWP 1611]
[New LWP 1612]
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
--Type <RET> for more, q to quit, c to continue without paging--
0x00007f2d694925ce in epoll_wait (epfd=5, events=0x7f2d68ede980, maxevents=10128, timeout=100)
    at ../sysdeps/unix/sysv/linux/epoll_wait.c:30
30      in ../sysdeps/unix/sysv/linux/epoll_wait.c
毫无疑问，这也是可以由detach命令，退出调试环境：

(gdb) detach 
Detaching from program: /home/szza/redis-6.0.5/redis-6.0.5/src/redis-server, process 1607
[Inferior 1 (process 1607) detached]
其他启动gdb的方式，可以参考官方文档：

https://sourceware.org/gdb/current/onlinedocs/gdb/Invoking-GDB.html#Invoking-GDB
运行程序
```
run

run 指令，简写是r，在启动gdb环境之后，用于运行待调试的程序。比如启动REDIS程序：

set args

如果待调试的程序需要输入参数，那么在启动gdb环境后、运行待调试程序前，使用set args指令来设置程序所需的输入参数。

quit，简写q

退出gdb调试界面命令是

break

break指令，简写是b，断点,用于在指定的地方加上断点，当程序运行至断点处就会暂停，便于调试。break指令如下：

break ：break后面没有任何参数，那么就在当前栈帧的下一个指令处加上断点

break line：在当前运行程序的line行处加断点。如果想在其他文件的某行添加断点，可以使用break filename:line指令。

break function：在当前运行程序的function处加上断点。

对于C++程序，可能会存在重载，甚至不同类存在同名函数，那么可以更加具体的设置：
```
break filename:function：在filename文件的 function 处加上断点
break filename:function(ArgsType...)：在filename文件的function(args)处加上断点，其参数类型ArgsType...
break class:function：在类class的function处加上断点，当然这里的函数可以加上具体参数类型
```
关于break指令能指定位置，可以参考：

https://sourceware.org/gdb/current/onlinedocs/gdb/Specify-Location.html#Specify-Location
break … if cond

但是如果只想在满足某个条件时，才触发断点，怎么办？

可以考虑使用break … if cond命令，其中...是上述break后的参数。

比如，以上面的main.cc程序为例，当cnt > 3的时候停止程序：

(gdb) break 7 if cnt > 3
Breakpoint 1 at 0x80011d0: file main.cc, line 7.
当程序运行到cnt >3时就会停止：

Breakpoint 1, main (argc=1, argv=0x7ffffffedfb8) at main.cc:7
7           cnt++;
(gdb) print cnt  # 显示 cnt 的值
$1 = 4
by the way

break … if cond指令有时候不会生效，比如：

(gdb) break main if cnt > 3
Breakpoint 2 at 0x80011a9: file main.cc, line 4.
整个程序运行结束，也不会触发。我猜测，条件断点需要在cnt每次产生值改变的位置加上判断条件，而这个位置刚好是第7行。

关于断点指令的更多信息，参考官方文档：

https://sourceware.org/gdb/current/onlinedocs/gdb/Set-Breaks.html#Set-Breaks
info b

查看断点信息，可以使用info breakpoints指令，简写是info b。

关于disable、enable的其余指令，可以参考：

https://sourceware.org/gdb/current/onlinedocs/gdb/Disabling.html#Disabling
执行流程

仅仅有断点还不行，还是需要进一步控制程序的执行流程。主要有以下三种：

next
step
continue
continue

continue指令，简写是c，用于恢复被break指令中断的程序，使其继续向下运行。

step  [count]

step [count]指令，简写是s，是逐步执行count个步骤，而不是count个语句、函数。当不写count时，默认就执行一步。

step指令，用于配合break指令一起使用：当在某个函数起始处触发断点，想要进入该函数体，则可以使用step指令。而step count则是一次性执行count步，避免繁琐的中间行为，比如避免C++中的构造函数等。

比如对于下面的C++程序：

int main(int argc, char const *argv[])
{
  std::unordered_map<int, int> map;
  map.insert({1,1}); // 第 6 行
  return 0;
}
想要在gdb中查看insert函数的原型，而忽略中间的{1,1}的构造过程：

(gdb) break 6
Breakpoint 1 at 0x1298: file main.cc, line 6.
(gdb) r
Starting program: /home/szza/stl/c++/demo/main 

Breakpoint 1, main (argc=1, argv=0x7ffffffedfb8) at main.cc:6
6         map.insert({1,1});
(gdb) s 9  # 一次性执行9步
std::unordered_map<int, int, std::hash<int>, std::equal_to<int>, std::allocator<std::pair<int const, int> > >::insert (this=0x7ffffffede64, __x=...)
    at /usr/include/c++/9/bits/unordered_map.h:585
585           insert(value_type&& __x)
(gdb) s   # 直接进入insert函数体
586           { return _M_h.insert(std::move(__x)); }
这样可以忽略中间构造std::pair<int, int>{1,1}的行为，直接进入insert函数中，使得调试更加清晰明了。

next [count]

next指令，简写是n，next指令是逐函数执行，即当停在断点触发的函数处：

step指令是逐步执行，下一步是会进入函数体中
next指令会直接执行完整个函数，然后进入下一行
对于 step [count]中的演示demo，如果是next指令，会直接执行完map.insert函数，进入下一行：

(gdb) r
Starting program: /home/szza/stl/c++/demo/main 

Breakpoint 1, main (argc=1, argv=0x7ffffffedfb8) at main.cc:6
6         map.insert({1,1});
(gdb) n  # 直接进入下一行
7         return 0;
(gdb) 
step、next合理的使用，控制调试的进度，使得调试更加方便。

set step-mode

如果某个函数、语句没有包含debug信息，gdb默认就会跳过这个函数、语句。但是，可以通过设置step-mode选项是否跳过：

set step-mode on：不跳过没有调试信息的函数、语句
set step-mode off：默认行为，跳过
可以通过show step-mmode来查看：

(gdb) show step-mode 
Mode of the step operation is off.
finish

finish指令，简写fin，用于将当前函数剩下的部分执行完毕，并且显示输出结果。

int countSum(int from, int to) {
  int sum =0;
  
  for (int from = 0; from < to; from++) 
  {
    sum += from;
  }
  sum+=1;
  sum+=2;
  sum+=3;
  sum+=4;
  sum+=5;
  sum+=6;
  sum+=7; 

  return sum; // 第16行
}

int main(int argc, char const *argv[]) {
 
  countSum(0, 10);
  return 0;
}
在countSum函数处添加断点，当该断点触发，执行step指令进入countSum函数。此时，直接执行finish指令，gdb会直接返回countSum的结果，然后进入下一行：

(gdb) break countSum(int, int) 
Breakpoint 1 at 0x1129: file main.cc, line 1.
(gdb) r
Starting program: /home/szza/stl/c++/demo/main 

Breakpoint 1, countSum (from=0, to=134222333) at main.cc:1
1       int countSum(int from, int to) {
(gdb) s                  // 进入函数体
2         int sum =0;
(gdb) finish 
Run till exit from #0  countSum (from=0, to=10) at main.cc:2
main (argc=1, argv=0x7ffffffedfb8) at main.cc:22
22        return 0;
Value returned is $1 = 73 // 直接执行完，并返回结果
finish指令默认会显示函数的返回结果，也可以设置为不显示。不过既然是调试，那么肯定是提供越多信息越好。

set print finish [on|off]：控制finish返回结果是否显示
show print finish：输出finish的返回结果是否显示
(gdb) show print finish
Printing of return value after `finish' is on.
return

return，指令与finish不同：

finish会把这个函数剩余的部分，正常运行完后在返回；
return指令，是直接在函数的当前位置返回，不管你执行到什么位置。
很好理解，就是finish把函数完整地执行完毕后返回，return是函数执行到某个位置，强行的返回，而不管函数的后续。

until [location]

until指令，简写u，可以用于直接跳出循环体。

比如上面的countSum函数，进入后，如果不想一直next单步执行，就执行until指令，会直接跳出for循环。

until

until指令，不加上参数，没有遇到循环体时功能类似于next，遇到了可以直接跳出循环体

(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/szza/stl/c++/demo/main 

Breakpoint 1, countSum (from=0, to=134222333) at main.cc:1
1       int countSum(int from, int to) {
(gdb) until    # 进入函数
2         int sum =0;
(gdb) until    # 遇到循环体
4         for (int from = 0; from < to; from++) 
(gdb) until    # 直接执行完循环体
6           sum += from;
(gdb) until
4         for (int from = 0; from < to; from++) 
(gdb) until    # 执行完循环体
8         sum+=1;
(gdb) until
9         sum+=2;
(gdb) until
10        sum+=3;
(gdb) 
until location

until location指令中的location格式和break location的格式一样，可以是行数、函数名。可以直接运行到指定行数。

以上面的countSum为例：

(gdb) break countSum(int, int) 
Breakpoint 1 at 0x1129: file main.cc, line 1.
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/szza/stl/c++/demo/main 

Breakpoint 1, countSum (from=0, to=134222333) at main.cc:1
1       int countSum(int from, int to) {
(gdb) s                     # 进入函数体
2         int sum =0;  
(gdb) until main.cc:16      # 一直执行到 return sum; 语句
countSum (from=0, to=10) at main.cc:16
16        return sum;
(gdb) n                     # 下一条就是函数返回了
17      }
会发现，直接运行到指定的位置：countSum函数的return语句处。

进一步，将main函数修改如下：

int main(int argc, char const *argv[]) {
 
  countSum(0, 10);
  countSum(10, 20);
  return 0;
}
如果我在执行countSum(0,10)函数时，突然想执行完当前函数，然后跳到转countSum(10,20)函数中，行不行呢？

当然是可以，可以借助until location指令实现。

(gdb) break countSum(int, int)                         # 先在countSum函数处加上断点
Breakpoint 1 at 0x1129: file main.cc, line 1.
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/szza/stl/c++/demo/main 

Breakpoint 1, countSum (from=0, to=10) at main.cc:1    # countSum(0, 10)第一次触发
1       int countSum(int from, int to) {
(gdb) s                                                # 进入函数体
2         int sum =0;  
(gdb) until main.cc:22                                 # 直接执行完当前函数，并跳转到 countSum(10, 20)
main (argc=1, argv=0x7ffffffedfb8) at main.cc:22
22        countSum(10, 20);
(gdb) s

Breakpoint 1, countSum (from=0, to=20) at main.cc:1   # 直接执行到countSum(10, 20)
1       int countSum(int from, int to) {
(gdb) s
2         int sum =0;
(gdb)
通过until指令，可以很好的控制函数的指令流程。更多指令可以参考：

https://sourceware.org/gdb/current/onlinedocs/gdb/Continuing-and-Stepping.html#Continuing-and-Stepping
显示

查看程序中运行时的变量的值，有两种方式：

print指令：手动输出
display指令：自动显示
下面分别讲解。

print

print指令，简写p，其格式如下两种。

print [[options] --] expr
print [[options] --] /f expr
print [[options] --] expr

print [[options] --] expr，其中expr可以是表达式、变量。其中，输出的变量，要么是全局变量、static变量，要么就是在当前作用域内可见的局部变量。

在多数情况下，print指令输出的结果就符合要求，但是有时候为了获得更好的显示，可以提供 options 选项，获得更好的输出。

比如，对于下面的代码：

int main(int argc, char const *argv[]) {
  
  std::vector<int> vec{1,2,3};
  return 0;
}
想要在gdb中显示vec的内容：

23        std::vector<int> vec{1,2,3};
(gdb) n
24        return 0;
(gdb) print vec            # 直接输出
$1 = std::vector of length 3, capacity 3 = {1, 2, 3}
(gdb) set print array on   # 开启数组显示
(gdb) print vec            # 有更好的输出显示
$2 = std::vector of length 3, capacity 3 = {
  1,
  2,
  3
}
(gdb) 
对于print的option选项设置，具体可以参考：

https://sourceware.org/gdb/current/onlinedocs/gdb/Data.html#Data
图片
print [[options] --] /f expr

print [[options] --] /f expr，其中/f是expr是输出格式：

    x  按十六进制格式显示变量
    d  按十进制格式显示变量
    u  按十六进制格式显示无符号整型
    o  按八进制格式显示变量
    t  按二进制格式显示变量
    a  按十六进制格式显示变量
    c  按字符格式显示变量
    f  按浮点数格式显示变量
    s  按字符串显示
    z  与'x'格式一样，该值被视为整数并被打印为十六进制，但是前导零被打印出来以便将该值填充为整数类型的大小
    r  'r'是'raw'的缩写，按照python的Pretty-printer风格进行打印
以上面的countSum函数为例，按照不同格式显示返回值sum：

(gdb) print sum 
$4 = 73
(gdb) print/a sum
$5 = 0x49
(gdb) print/c sum
$7 = 73 'I'
(gdb) p/x $pc  # 当前指令指向的地址
$23 = 0x807c6fa
顺便说下，$pc表示当前指令地址，因此print/x $pc是以16进制显示当前指令的地址。

关于输出流格式信息，原文参考：

https://sourceware.org/gdb/current/onlinedocs/gdb/Output-Formats.html#Output-Formats
display

print指令，是手动输出表达、变量的值。display可以让指定的表达式、变量在每次的单步执行中自动显示。主要有以下三种使用方式：

display   expr
display/f expr
display/f addr
display /f expr

display /f expr 的使用，和print的格式基本一致。

比如，在countSum函数中，想要观察变量的sum值，由于是在一个循环体中，一直使用print指令查看sum变量的值，不免过于麻烦。此时，使用display指令来查看，使得gdb在运行每条语句的时候都会显示一次sum的值。

效果如下：

Breakpoint 1, countSum (from=0, to=134222349) at main.cc:1
1       int countSum(int from, int to) {
(gdb) s
2         int sum =0;
(gdb) n
4         for (int from = 0; from < to; from++) 
(gdb) display sum  # display 指令
1: sum = 0
(gdb) n            # 每条指令都会显示 sum 的值
6           sum += from;
1: sum = 0         # 每条指令都会显示 sum 的值
(gdb) 
4         for (int from = 0; from < to; from++) 
1: sum = 0         # 每条指令都会显示 sum 的值
(gdb) 
6           sum += from;
1: sum = 0
(gdb) 
4         for (int from = 0; from < to; from++) 
1: sum = 1
...
display /f addr

当自动显示的是地址时，可以使用/i格式描述符，查看地址 addr的汇编代码，$pc指向的当前指令的地址。

因此display /i &pc这条指令，可以查看当前指令对应的汇编代码。

Breakpoint 1, countSum (from=0, to=134222349) at main.cc:1
1       int countSum(int from, int to) {
(gdb) display sum    # 设置自动显示 sum 变量
1: sum = 134222272
(gdb) display /i $pc # 设置显示当前代码的汇编
2: x/i $pc
=> 0x8001129 <countSum(int, int)>:      endbr64 
(gdb) n              # 每一步都会显示上面的两个设置
2         int sum =0;
1: sum = 134222272
2: x/i $pc
=> 0x8001137 <countSum(int, int)+14>:   movl   $0x0,-0x8(%rbp)
关于输出显示的指令的输出显示信息，可以参考：

https://sourceware.org/gdb/current/onlinedocs/gdb/Data.html#Data
栈帧

backtrace

backtrace指令，简写bt，可以在break指令设置的断点触发时，查看程序是怎么执行到此断点处的，追踪下栈帧信息。

比如，在REDIS程序中，setCommand函数处的断点触发时，想要看看REEDIS是怎么从main函数执行到setCommand函数的，可以使用bt指令来追踪下栈帧轨迹：

Thread 1 "redis-server" hit Breakpoint 1, setCommand (c=0x8042e22 <dictGenCaseHashFunction+47>)
    at t_string.c:99
99      void setCommand(client *c) {
(gdb) bt
#0  setCommand (c=0x7fffff11c680) at t_string.c:101
#1  0x000000000804a765 in call (c=0x7fffff11c680, flags=15) at server.c:3301
#2  0x000000000804b73c in processCommand (c=0x7fffff11c680) at server.c:3695
#3  0x000000000805e24f in processCommandAndResetClient (c=0x7fffff11c680) at networking.c:2057
#4  0x000000000805e4ae in processInputBuffer (c=0x7fffff11c680) at networking.c:2169
#5  0x000000000805e874 in readQueryFromClient (conn=0x7fffff015140) at networking.c:2275
#6  0x000000000810888b in callHandler (conn=0x7fffff015140, handler=0x805e52e <readQueryFromClient>) at connhelpers.h:79
#7  0x0000000008108f57 in connSocketEventHandler (el=0x7fffff00b480, fd=8, clientData=0x7fffff015140, mask=1) at connection.c:330
#8  0x0000000008040cad in aeProcessEvents (eventLoop=0x7fffff00b480, flags=27) at ae.c:497
#9  0x0000000008040eeb in aeMain (eventLoop=0x7fffff00b480) at ae.c:558
#10 0x000000000804fac3 in main (argc=1, argv=0x7ffffffedf48) at server.c:5236
(gdb) 
从bt指令的输出信息可以看出整个调用链，是如何从main函数执行到setCommand函数的，这对于理清项目框架至关重要，尤其是大量使用回调函数的项目中，比如REDIS、Libuv。

frame N

frame指令，简写f，frame N表示跳转到编号为N的栈帧中，不加参数的frame 指令，可以显示当前栈帧的基本信息。

上面的bt指令，可以详细地看到从main函数运行到setCommnad函数的调用过程。但是，如果我想看看其中某一个栈帧的调用过程，那怎么办？

比如，现在我就想知道REDIS是怎么处理客户端的请求的，想去processInputBuffer函数所在栈帧，那么就如下操作：

(gdb) frame 5
#5  0x000000000805e874 in readQueryFromClient (conn=0x7fffff015140) at networking.c:2275
2275         processInputBuffer(c);
(gdb) s                            # 进入 processInputBuffer 函数
101         robj *expire = NULL;                
frame N 中 N 是调用 processInputBuffer 函数的栈帧，即 processInputBuffer  函数的上一个栈帧，由于 processInputBuffer  函数是在 readQueryFromClient 函数中被调用，因此要查看processInputBuffer函数，需要进入readQueryFromClient所处的栈帧，因此 N=5。

info frame

info frame指令，简写info f，会显示当前栈帧的详细信息，比如：当前调用函数的地址，被调用函数的地址，源码语言、函数参数地址及值、局部变量的地址等等。

比如，当前执行到setCommand函数中，那么info f就可以查看当前的栈帧：

(gdb) info frame
 Stack level 0, frame at 0x7ffffffedae0:     # 当前函数栈帧地址 
 rip = 0x807c6fa in setCommand (t_string.c:101); saved rip = 0x804a765
 called by frame at 0x7ffffffedb60           # 当前函数在哪里被调用的
 source language c.                          # c 语言写的
 Arglist at 0x7ffffffeda78, 
 args: c=0x7fffff11c680                      # 函数参数
 Locals at 0x7ffffffeda78, Previous frame's sp is 0x7ffffffedae0
 Saved registers:
  rbx at 0x7ffffffedac8, rbp at 0x7ffffffedad0, rip at 0x7ffffffedad8
info args

info args指令，可以获取当前栈帧函数 setCommand 的参数名及其值。

setCommand 的原型是 setCommand(client *c) ，其参数是指针类型，因此获得参数c值后，可以打印参数c指向的数据。比如，现在想看看 setCommand 的参数c中的字段c->argv的第一个字符串是不是set：

(gdb) info args 
c = 0x7fffff11c680                # 和 info frame 显示的地址一致
(gdb) print (const char*)((client*)0x7fffff11c680)->argv->ptr
$16 = 0x7fffff134d93 "set"        # 确实是set
info locals

打印出当前函数中所有局部变量及其值。

(gdb) info locals 
j = 0
expire = 0x7fffff009031
unit = -75072
flags = 32767
关于栈帧的更多信息，可以参考：

https://sourceware.org/gdb/current/onlinedocs/gdb/Stack.html#Stack
补充

shell

如果想要在gdb环境中，执行Linux命令，可以在指令前加上shell即可，比如clear命令，在gdb下执行为：

(gdb) shell clear
空行

在gdb下，直接回车，即输入一个空行，相当于重复执行上一条指令。

比如，在 setCommand 函数触发时：

Thread 1 "redis-server" hit Breakpoint 1, setCommand (c=0x8042e22 <dictGenCaseHashFunction+47>)
    at t_string.c:99
99      void setCommand(client *c) {
(gdb) s
101         robj *expire = NULL;                //* 超时时间
(gdb) n
102         int unit = UNIT_SECONDS;            //* 超时的时间单位
(gdb)    # 空行就是重复执行 next
103         int flags = OBJ_SET_NO_FLAGS;       //* set 指令的类型
(gdb)    # 空行就是重复执行 next
107         for (j = 3; j < c->argc; j++) {
(gdb) 