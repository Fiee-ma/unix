#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(){

    int pid, i;
    int group1, group2;

    //设置父进程为组长
    setpgid(getpid(), getpid());
    group1 = getpgid(getpid());

    for(i = 1; i <= 3; ++i){
        pid = fork();
        if(pid > 0){
            if(i == 1)
                setpgid(pid, pid);
            else if(i == 2){
                setpgid(pid, pid);
                group2 = getpgid(pid);
            }
            else if(i == 3){
                setpgid(pid, group2);
            }
        }
        if(pid == 0){
            if(i == 1)
                setpgid(getpid(), group1);   //如果group1不存在，就会出现错误
            else if(i == 2){
                setpgid(getpid(), getpid());
                group2 = getpgid(getpid());
            }
            else if(i == 3){
                //如果进程２还未运行，这时group2就会出错，或者进程2的进程３还未运行时就运行完成，也会出错
                setpgid(getpid(), group2);
                //sleep(1);
            }
            break;
        }
        if(pid < 0){
            perror("fork");
            return -1;
        }
    }
    printf("进程%d, pid = %d -> ppid = %d, gpid = [%d], (%s)\n", i%4, getpid(), getppid(), getpgid(getpid()), strerror(errno));

    return 0;
}
