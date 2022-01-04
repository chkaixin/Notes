# System V IPC（进程间通信）

## 信号量

1.semget系统调用

创建一个新的信号量集，或者获取一个已经存在的信号量集
```c
#include <sys/sem.h>
int semget(key_t key, int num_sems, int sem_flags);
```

2.semop系统调用

改变信号量的值，即执行P、V操作
```c
#include <sys/sem.h>
int semop(int sem_id, struct sembuf* sem_ops, size_t num_sem_ops);
```

3.semctl系统调用

允许调用者对信号量进行直接控制
```c
#include <sys/sem>
int semctl(int sem_id, int sem_num, int command, ...);
```