#include<unistd.h>
#include<string.h>
#include<stdio.h>

int main(){

    printf("test\n");
    char *argv[] = {"ls", "-l", NULL};
    if(execvp("ls", argv) == -1){
        perror("exec");
        return 1;
    }

    printf("test1\n");

    return 0;
}
