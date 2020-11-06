#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

    char *filename = argv[1];
    int length = atoi(argv[2]);
    truncate(filename, length);

    return 0;
}
