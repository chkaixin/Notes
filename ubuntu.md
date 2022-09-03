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