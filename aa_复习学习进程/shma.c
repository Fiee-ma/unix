#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>

int main(){

    //shmget函数通过事先约定的键值0x8888创建(IPC_CREAT)一个内核对象并返回其id。
    //如果0x8888对应的内核对象存在，就失败(IPC_EXCL)。0664是该内核内核对象的权限
    //第二个参数表示创建的共享内存大小
    int id = shmget(0x8888, 4096, IPC_CREAT | IPC_EXCL | 0664);
    //如果失败就退出
    if(id < 0){
        perror("shmget");
        return -1;
    }

    //打印获取的内核对象id
    printf("id = %d\n", id);

    //使用函数shmat(share memory attach)将内核对象维护的内存挂接到一个用户空间的线性地址
    char *buf = shmat(id, NULL, 0); //若第二个参数为0，则系统帮你选取一个合适的地址，第三个参数表示是以只读或者读写方式打开

    //如果挂接失败就退出
    if(buf == (char*)-1){
        perror("shmat");
        return -1;
    }

    //将数据拷贝到共享内存中
    strcpy(buf, "hello,share momeory\n");

    //使用shmdt(share memory detach)将挂接内存卸载
    if(shmdt(buf) < 0){
        perror("shmdt");
        return -1;
    }

    return 0;
}

















