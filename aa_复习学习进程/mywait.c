#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>

void handler(int sig){
    printf("haha");
}

int main(){

    pid_t pid;

    if(SIG_ERR == signal(SIGINT, handler) > 0){
        perror("signal");
        return 1;
    }
    printf("fork child process before\n");

    for(int i = 0; i < 5; i++){
        pid = fork();
        if(pid == 0)
            break;   //子进程退出while循环
        else if(pid < 0){
            perror("fork");
            return 1;
        }
    }
    if(pid == 0){
//        sleep(3);
        printf("child process pid = %d, father pid = %d\n", getpid(), getppid());
        return 0;
    }

    while(1){
        sleep(5);
        pid = wait(NULL);
        if(pid == -1){
            perror("wait");
            sleep(10);
            printf("l'm father pid = %d, l have wait all zombies\n", getpid());
            return 1;
        }
        printf("l'm father pid = %d, child %d exit\n", getpid(), pid);
    }

    return 0;
}
