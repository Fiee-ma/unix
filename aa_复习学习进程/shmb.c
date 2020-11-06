#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<stdio.h>

int main(){

    //根据事先约定的键值来获取内核内存对应的id,后两个参数都可以制定为0
    int id = shmget(0x8888, 0, 0);
    if(id < 0){
        perror("shmget");
        return -1;
    }

    printf("id = %d", id);
    //挂接内存
    char *buf = shmat(id, NULL, 0);
    if(buf == (char*)-1){
        perror("shmat");
        return -1;
    }

    //打印数据
    printf("buf = %s", buf);

    //卸载挂接的内存
    if(shmdt(buf) < 0){
        perror("shmdt");
        return -1;
    }

    //删除内核共享内存
    if(shmctl(id, IPC_RMID, NULL)){
        perror("shmctl");
        return -1;
    }

    return 0;
}
