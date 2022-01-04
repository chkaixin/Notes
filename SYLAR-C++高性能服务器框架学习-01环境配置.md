# SYLAR-C++高性能服务器框架学习-01环境配置

## 环境配置

1. Linux系统
2. VIM7.4
3. GCC 4.8+
4. GDB 8.3

## 将自定义安装路径添加到PATH

把要用到的程序都安装到一个自定义路径，不会与系统路径冲突。可以多版本并存。

需要将自定义的路径加入到PATH中

export PATH=/apps/sylar/bin:$PATH

export LD_LIBRARY_PATH=/apps/sylar/lib:/apps/sylar/lib64:$LD_LIBRARY_PATH

将以上语句添加到~/.profile 或者 /etc/profile 文件最后。

执行source ~/.profile 或者 source /etc/profile
(我的自定义路径是/apps/sylar)

执行echo $PATH(验证是否设置成功)

## Linux系统安装

虚拟机安装centos7.6系统或者购买阿里云或腾讯云搭建系统

## VIM安装

代码中使用了C++11，所以必须使用VIM7.4以上的版本才能正常显示C++11中的一些语法(lambda)。

安装VIM8.1，链接地址: ftp://ftp.vim.org/pub/vim/unix/vim-8.1.tar.bz2

```
#安装依赖
yum install wget
yum install ncurses-devel
yum install gcc gcc-c++
yum install ctags
yum install bzip2
yum install git

wget ftp://ftp.vim.org/pub/vim/unix/vim-8.1.tar.bz2
tar xvf vim-8.1.tar.bz2
cd vim81
./configure --prefix=/apps/sylar
make -j4
make install

#验证安装成功
which vim
/apps/sylar/bin/vim
```

```
git clone https://github.com/sylar-yin/myvim.git
cp myvim/.vim ~/ -rf
cp myvim/.vimrc ~/
```

`alias vctags="ctags -R --c++-kinds=+p --fields=+iaS --extra=+q"`
#添加到/etc/profile末尾

## GCC安装

9.1版本以上能完整支持C++11，C++14，C++17，而且错误提示更友好

链接地址：http://ftp.gnu.org/gnu/gcc/gcc-9.1.0/gcc-9.1.0.tar.xz

### 安装bison

没有安装bison，编译中会提示 `“WARNING: ‘bison’ is missing on your system.”`

```
sudo yum install bison
```

### 安装texinfo

没有安装texinfo，编译中会提示`“WARNING: ‘makeinfo’ is missing on your system”`

```
sudo yum install texinfo
```

### 安装autoconf

gcc安装需要依赖automake-1.15以上版本，automake-1.15以上版本，需要依赖autoconf 2.69

下载地址：http://ftp.gnu.org/gnu/autoconf/autoconf-2.69.tar.gz

```
wget http://ftp.gnu.org/gnu/autoconf/autoconf-2.69.tar.gz
tar xvf autoconf-2.69.tar.gz
cd autoconf-2.69
./configure --prefix=/apps/sylar
make -j4
make install

#验证安装成功
which autoconf
/apps/sylar/bin/autoconf
```

### 安装automake

gcc安装需要依赖automake-1.15以上版本

下载地址：http://ftp.gnu.org/gnu/automake/automake-1.15.tar.gz

```
wget http://ftp.gnu.org/gnu/automake/automake-1.15.tar.gz
tar xvf automake-1.15.tar.gz
cd automake-1.15
./configure --prefix=/apps/sylar
#修改Makefile 查找 /doc/automake-$(APIVERSION)
#doc/automake-$(APIVERSION).1: $(automake_script) lib/Automake/Config.pm
#    $(update_mans) automake-$(APIVERSION) --no-discard-stderr
#(3686行，加上--no-discard-stderr)
make -j4
make install

#验证安装成功
which automake
/apps/sylar/bin/automake
```

### GCC正式安装

GCC安装的时间会比较长，大概半小时-2小时，取决于机器性能，需要耐心等待

```
wget http://ftp.gnu.org/gnu/gcc/gcc-9.1.0/gcc-9.1.0.tar.xz
tar xvJf gcc-9.1.0.tar.xz
cd gcc-9.1.0
./contrib/download_prerequisites
mkdir build
cd build
../configure --enable-checking=release --enable-languages=c,c++ --disable-multilib --prefix=/apps/sylar
make -j4
make install

#验证安装成功
which gcc
/apps/sylar/bin/gcc
```

## GDB安装

linux下调试工具, 版本8.3

由于8.3版本需要依赖gcc支持c++11，gdb必须等gcc安装完之后再安装

下载地址：http://ftp.gnu.org/gnu/gdb/gdb-8.3.tar.xz

```
wget http://ftp.gnu.org/gnu/gdb/gdb-8.3.tar.xz
tar xvf gdb-8.3.tar.xz
cd gdb-8.3
./configure --prefix=/apps/sylar
make -j4
make install

#验证安装成功
which gdb
/apps/sylar/bin/gdb
```

## CMake安装

我使用的版本是CMake3.14.5

下载地址：https://cmake.org/files/v3.14/cmake-3.14.5.tar.gz

```
wget https://cmake.org/files/v3.14/cmake-3.14.5.tar.gz
tar xvf cmake-3.14.5.tar.gz
cd cmake-3.14.5
./configure --prefix=/apps/sylar
make -j4
make install

#验证安装成功
which cmake
/apps/sylar/bin/cmake
```

## Ragel安装

有限状态机，编写出来的协议解析性能不弱于汇编

我使用的版本是Ragel 6.10,

下载地址：http://www.colm.net/files/ragel/ragel-6.10.tar.gz

```
wget http://www.colm.net/files/ragel/ragel-6.10.tar.gz
tar xvf ragel-6.10.tar.gz
cd ragel-6.10
./configure --prefix=/apps/sylar
make -j4
make install

#验证安装成功
which ragel
/apps/sylar/bin/ragel
```

## boost安装

```
yum install boost-devel
```

## 其他

```
#killall 安装
yum install psmisc
#openssl 安装
yum install openssl-devel
#netstat 安装
yum install net-tools
```