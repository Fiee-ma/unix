#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<errno.h>

#define ASSERT(msg, res)if((res) < 0){perror(#msg); exit(-1);}

typedef struct{

    char name[20];
    int age;
}Person;

typedef struct{

    long type;
    Person person;
}Msg;

void printMsg(Msg *msg){

    printf("type = %ld, name = %s, age = %d\n", msg->type, msg->person.name, msg->person.age);
}

int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Usage: %s <type>\n", argv[0]);
        return -1;
    }
    //想要获取的类型
    long type = atol(argv[1]);

    //获取信号队列的id
    int id = msgget(0x8888, 0);
    ASSERT(msgget, id);

    Msg msg;
    //开始读取信号队列中的信息
    while(1){
        int res = msgrcv(id, &msg, sizeof(Person), type, IPC_NOWAIT);
        if(res < 0){
            if(errno == ENOMSG){
                printf("no message\n");
                break;
            }
            else
                ASSERT(msgrcv, res);
        }

        //打印消息内容
        printMsg(&msg);
    }

    return 0;
}

