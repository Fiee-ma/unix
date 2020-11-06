#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void handler(int sig){

    while(sig == SIGINT)
        printf("signal %d\n", sig);
    sleep(5);
}

int main(){

    if(SIG_ERR == signal(SIGINT, handler))
        perror("signal");

    while(1)
        pause();
}
