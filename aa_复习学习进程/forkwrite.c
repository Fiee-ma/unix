#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdio.h>

int main(){

    int fd = open("test.file", O_WRONLY | O_CREAT, 0644);
    if(fd == -1)
        perror("open");
    printf("l'm father\n");
    printf("before fork\n");

    pid_t pid = fork();

    if(pid > 0){
        sleep(3);
        write(fd, "hello", 5);
        close(fd);
    }
    else if(pid == 0){
        write(fd, "world", 5);
        sleep(5);
        write(fd, "lalala", 6);
        close(fd);
    }
    else{
        perror("fork");
        return 1;
    }

    return 0;
}
