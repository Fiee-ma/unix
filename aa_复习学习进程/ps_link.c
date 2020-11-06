// ps_link.c
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int pid, i = 4;


  while(i--) {
    pid = fork();
    if (pid > 0) {
      // 如果是父进程，产生了子进程后就必须退出循环。
      // 因为按照进程链定义，一个父进程只能产生一个子进程。
      break;
    }
    else if (pid < 0) {
      perror("fork");
      return -1;
    }
  }

  printf("pid: %d -> ppid: %d\n", getpid(), getppid());
  while(1) sleep(1);
  return 0;
}
