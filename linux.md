# Linux命令

find / -name xxx.x: 查找:

mkdir -p: 递归创建目录; mkdie -p aa/xx.cc 如果aa目录不存在，也创建

chmod u+x ex1.py: 为 ex1.py 文件拥有者增加可执行权限
chmod 777 ex1.py: 所有用户添加读写执行权限

export: 在 shell 中执行程序时，shell 会提供一组环境变量。export 可新增，修改或删除环境变量，供后续执行的程序使用。export 的效力仅限于该次登陆操作

export PATH=/apps/sylar/bin:$PATH

export会覆盖，所以加上$PATH:的目的就是保留所有的path变量，操作系统会通过:切割找到匹配路径

cp: cp -r 源 目标

-r: 若给出的源文件是一目录文件，此时cp将递归复制该目录下所有的子目录和文件。此时目标文件必须为一个目录名。

EOF: 一般会配合cat能够多行文本输出.

其用法如下:

```
<<EOF        //开始
....
EOF            //结束
```

还可以自定义，比如自定义：

```
<<BBB        //开始
....
BBB              //结束
```

通过cat配合重定向能够生成文件并追加操作,在它之前先熟悉几个特殊符号:

```
< :输入重定向
> :输出重定向
> 
>> :输出重定向,进行追加,不会覆盖之前内容
<< :标准输入来自命令行的一对分隔号的中间内容.
```

## 修改环境变量

export PATH=/apps/sylar/bin:$PATH

export LD_LIBRARY_PATH=/apps/sylar/lib:/apps/sylar/lib64:$LD_LIBRARY_PATH

将以上语句添加到~/.profile 或者 /etc/profile 文件最后。

执行source ~/.profile 或者 source /etc/profile
(我的自定义路径是/apps/sylar)

执行echo $PATH(验证是否设置成功)