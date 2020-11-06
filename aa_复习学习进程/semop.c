#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<stdlib.h>

void printSem(int id){

    unsigned short vals[3] = {0};
    semctl(id, 0, GETALL, vals);
    printf("R0 = %d, R1 = %d, R2 = %d\n", vals[0], vals[1], vals[2]);
}

int main(){

    int id = semget(0x8888, 3, IPC_CREAT | IPC_EXCL | 0664);

    //打印当前信号量值
    puts("信号量初始值为：");
    printSem(id);

    //１、设置第二个信号量值
    semctl(id, 2, SETVAL, 20);
    puts("１、设置第二个信号量值为20");
    printSem(id);

    //2、设置三个信号量值分别为12,5,9
    puts("２、设置三个信号量值分别为12,5,9");
    unsigned short vals[3] = {12, 5, 9};
    semctl(id, 0, SETALL, vals);
    printSem(id);

    //3、请求2个R0资源
    puts("３、请求2个R0资源");
    struct sembuf op1 = {0, -2, 0};
    semop(id, &op1, 1); //第三个参数表示数组的大小
    printSem(id);

    //4、请求３个R1和５个R2
    puts("4、请求３个R1和５个R2");
    struct sembuf ops[2] = {{1, -3, 0}, {2, -5, 0}};
    semop(id, ops, 2);
    printSem(id);

    //5、释放２个R1
    puts("5、释放２个R0");
    struct sembuf op2 = {0, 2 ,0};
    semop(id, &op2, 1);
    printSem(id);

    //6、释放３个R1和５个R2
    struct sembuf ops1[2] = {{1, 3, 0}, {2, 5, 0}};
    puts("6、释放３个R1和５个R2");
    semop(id, ops1, 2);
    printSem(id);

    return 0;
}
