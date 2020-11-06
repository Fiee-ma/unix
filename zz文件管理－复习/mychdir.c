#include<unistd.h>
#include<stdio.h>

int main(int argc, char *argv[]){

    if(chdir(argv[1]) == -1){
        perror("chdir");
        return -1;
    }

    printf("current dir: %s\n", getcwd(NULL, 0));
    return 0;
}
