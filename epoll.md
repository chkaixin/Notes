# epoll

## epoll LT

高电平触发

1.EPOLLIN事件

内核socket接受缓冲区 为空 低电平

内核socket接受缓冲区 非空 高电平

2.EPOLLOUT事件

低电平->高电平 触发

高电平->低电平 触发

内核socket发送缓冲区 不满 高电平

内核socket发送缓冲区 为满 低电平

## epoll ET

EPOLLIN事件，内核socket接受缓冲区从无->有（低电平->高电平）

EPOLLOUT事件，内核socket发送缓冲区从满->不满（低电平->高电平）