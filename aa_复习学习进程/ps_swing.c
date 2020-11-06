// ps_swing.c
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int pid, i = 4;

  while(i--) {
    pid = fork();
    if (pid == 0) {
      // 如果是子进程，就不能继续循环了。
      // 按照进程扇的定义，子进程是没有子进程的。
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
