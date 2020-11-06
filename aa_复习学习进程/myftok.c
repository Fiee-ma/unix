#include<unistd.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Usage: %s <path> <id>\n", argv[0]);
        return -1;
    }

    int id = atoi(argv[2]);

    key_t key = ftok(argv[1], id);
    if(key == -1){
        perror("ftok");
        return -1;
    }

    printf("key = 0x%08x\n", key);
    return 0;
}
