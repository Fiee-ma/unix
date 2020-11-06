#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<pwd.h>

void handler(int sig){

    getpwnam("root");
}

int main(){

    if(SIG_ERR == signal(SIGINT, handler) > 0){
        perror("signal");
        return 1;
    }

    printf("l'm pid = %d\n", getpid());
    struct passwd *pwd = getpwnam("marulong");
    sleep(10);
    printf("uid = %d\n", pwd->pw_uid);

    return 0;
}
