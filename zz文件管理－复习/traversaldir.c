#include<unistd.h>
#include<dirent.h>
#include<stdio.h>
#include<sys/types.h>

void traversal(DIR *dir){

    struct dirent *de = NULL;
    while((de = readdir(dir)) != NULL){
        printf("%ld\t0x%02x\t%ld\t%s\n", de->d_ino, de->d_type,de->d_off, de->d_name);
    }
}

int main(int argc, char *argv[]){

    DIR *dp = opendir(argv[1]);
    if(!dp){
        perror("opendir");
        return -1;
    }

    traversal(dp);
    closedir(dp);
}
