#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<setjmp.h>
#include<signal.h>
#include<setjmp.h>

jmp_buf jmpbuf;
void handler(int sig){

    printf("hello!l'm sigint\n");
    sleep(8);
    siglongjmp(jmpbuf, 1);
}

int main(){

    if(SIG_ERR == signal(SIGINT, handler) > 0){
        perror("signal");
        return 1;
    }
    if(sigsetjmp(jmpbuf, 1) != 0){
        printf("return int\n");
    }

    while(1){
        sleep(10);
    }

    return 0;
}
