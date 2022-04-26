# centos环境配置

```
yum install git

yum install zsh
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

更新cmake,我使用的版本是CMake3.14.5
下载地址：https://cmake.org/files/v3.14/cmake-3.14.5.tar.gz
wget https://cmake.org/files/v3.14/cmake-3.14.5.tar.gz
tar xvf cmake-3.14.5.tar.gz
cd cmake-3.14.5
./bootstrap
gmake
gmake install
查看新版本
/usr/local/bin/cmake --version
删除原来cmake版本，建立软连接，测试
yum remove cmake -y
ln -s /usr/local/bin/cmake /usr/bin/
cmake --version
```

## 查看gcc

查看gcc版本: 

yum info gcc

### 依赖库

yum install -y gcc gcc-c++

### 下载并且安装gcc

yum install -y wget

yum install -y bzip2

```
wget http://ftp.gnu.org/gnu/gcc/gcc-9.1.0/gcc-9.1.0.tar.xz
tar xvJf gcc-9.1.0.tar.xz
cd gcc-9.1.0
./contrib/download_prerequisites
mkdir build
cd build
../configure --enable-languages=c,c++ --disable-multilib --prefix=/usr/local/gcc-9.1.0
make -j4
make install
```

### 环境变量

vim /etc/profile 下方添加:
```
export PATH=/usr/local/gcc-9.1.0/bin/:$PATH
export LD_LIBRARY_PASH=$LD_LIBRARY_PATH:/usr/local/gcc-9.1.0/lib64/
export CC=/usr/local/gcc-9.1.0/bin/gcc
export CXX=/usr/local/gcc-9.1.0/bin/g++
```

echo $PATH 验证配置完成

注意: 如果未设置以上环境变量时,执行cmake报错,删除cmake生成的文件

### 动态库设置软连接

find / -name "libstdc++.so*" 输出: 

cd /usr/lib64

ll stdlibc++*

rm libstdc++.so.6

将上面的最新动态库libstdc++.so.6.0.21复制到/usr/lib64目录下：

cp /usr/local/gcc-9.1.0/lib64/libstdc++.so.6.0.26 /usr/lib64

ln -s libstdc++.so.6.0.26 libstdc++.so.6

默认动态库升级完成。重新运行以下命令检查动态库: 

strings /usr/lib64/libstdc++.so.6 | grep GLIBC

### 安装nginx

yum -y install epel-release
yum -y install nginx --enablerepo=epel