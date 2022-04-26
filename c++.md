# 学习视频
候捷c++教程 油管
os:https://cnmooc.org/portal/session/14956-study.mooc
哈工大李治军老师  操作系统  虚拟内存那块

# stream
IO类继承关系
![avatar](/image/c++_stream.png)

1. iostream：控制台输入输出
cin，cout都是iostream类的对象，<<,>>是操作符重载。
cin>>a;//从控制台接收输入并保存在a中
cout<<a;//把a的值输出到控制台
2. stringstream：string的输入输出
istringstream a(b); //将a和string类型的b相关联
string c;
while(a>>c) //a从b中读取东西并保存在c中(从a往c“扔”东西)
a.str(); //a的内容
ostringstream d;
d<<"abcdefg"; //将字符串保存到d中(“扔”到d里面)
d.str(); //d的内容
3. fstream：文件相关的输入输出

# 知识点

## std::string::size_type

size_type是容器概念，没有容器不能使用。

由string类类型和vector类类型定义的类型，用以保存任意string对象或vector对象的长度，标准库类型将size_type定义为unsigned类型

string抽象意义是字符串， size（）的抽象意义是字符串的尺寸， string::size_type抽象意义是尺寸单位类型

string::size_type它在不同的机器上，长度是可以不同的，并非固定的长度。但只要你使用了这个类型，就使得你的程序适合这个机器。与实际机器匹配。

string::size_type从本质上来说，是一个整型数。关键是由于机器的环境，它的长度有可能不同。 例如：我们在使用 string::find的函数的时候，它返回的类型就是 string::size_type类型。而当find找不到所要找的字符的时候，它返回的是 npos的值，这个值是与size_type相关的。假如，你是用 string s; int rc = s.find(.....); 然后判断，if ( rc == string::npos ) 这样在不同的机器平台上表现就不一样了。如果，你的平台的string::size_type的长度正好和int相匹配，那么这个判断会侥幸正确。但换成另外的平台，有可能 string::size_type的类型是64位长度的，那么判断就完全不正确了。 所以，正确的应该是： string::size_type rc = s.find(.....); 这个时候使用 if ( rc == string::npos )就回正确了

## capacity()

capacity在不分配新的内存空间的下可以保存多少元素。

https://blog.csdn.net/JIEJINQUANIL/article/details/51166154