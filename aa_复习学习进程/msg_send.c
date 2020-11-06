#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define ASSERT(msg, res)if((res) < 0){perror(#msg); exit(-1);}

typedef struct{

    char name[20];
    int age;
}Person;

typedef struct{

    long type;
    Person person;
}Msg;

int main(){

    int id = msgget(0x8888, IPC_CREAT | 0664);
    ASSERT(msgget, id);

    Msg msg[10] = {
        {1, {"Luffy", 17}},
        {1, {"Zoro", 19}},
        {2, {"Nami", 18}},
        {2, {"Usopo", 17}},
        {1, {"Sanji", 19}},
        {3, {"Robin", 28}},
        {4, {"Chopper", 19}},
        {4, {"Franky", 34}},
        {5, {"Brook, 88", 20}},
        {6, {"Sunny", 2}}
    };

    int i;
    for(i = 0; i < 10; ++i){
        int res = msgsnd(id, &msg[i], sizeof(Person), 0);
        ASSERT(msgsend, res);
    }

    return 0;
}
