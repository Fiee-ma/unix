#include<unistd.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

void child(int fd[2]){

    close(fd[1]);  //关闭写端
    char buf[64] = {0};
    int n, i;

    while(1){
        n = read(fd[0], buf, 64);
        //puts("begin read data");
        for(i = 0; i < n; ++i)
            putchar(toupper(buf[i]));
        if(*buf == 'q'){
            close(fd[0]);
            exit(0);
        }
        if(n == 0){
            puts("no data read");
            sleep(1);
        }
    }

    exit(0);
}

int main(){

    int fd[2];
    int n;
    char buf[64] = {0};
    if(pipe(fd) < 0){    //建立一个管道
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if(pid == 0){
        child(fd);
    }

    close(fd[0]); //关闭读端，千万不可以在fork()前关闭

    while(1){
        n = read(STDIN_FILENO, buf, 64);
        write(fd[1], buf, n);
        if(*buf == 'q'){
            close(fd[1]);
            return 0;
        }
    }

    return 0;
}




















