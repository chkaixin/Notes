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


