# ubuntu 20.04

### 安装redis

sudo apt-get install -y redis-server

### 设置密码

```
sudo vim /etc/redis/redis.conf
修改配置文件里的requirepass,把注释关掉,然后后面改为你想设置的密码,然后再重新启动redis即可
service redis restart
```
### 查看已安装软件

```
dpkg -l | grep xxx
```

### 配置c/c++环境
ubantu 并没有提供C/C++的编译环境，单独安装gcc以及g++比较麻烦，Ubuntu提供了一个build-essential软件包，安装了该软件包，编译c/c++所需要的软件包也都会被安装

### 1、安装 C语言编译器 gcc，安装 C++语言编译器 g++，安装程序调试器 gdb
sudo apt update

####通过以下命令安装编译器和调试器，gdb是Linux下常用的程序调试器
sudo apt install build-essential gdb

### 如果成功，则显示版本号
gcc --version
g++ --version
gdb --version

### 2、CMake安装

### 通过以下命令安装cmake
sudo apt install cmake

### 如果成功，则显示版本号
cmake --version