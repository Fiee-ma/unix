#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char *argv[]){

    if(mkdir(argv[1], 0775) == -1){
        perror("mkdir");
        return -1;
    }

    return 0;
}
