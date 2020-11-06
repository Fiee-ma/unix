#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  pid_t sid, pid;
  pid = fork();
  if (pid == 0) {
    // 子进程不可能是进程组组长，可以让其创建新的会话，
    // 同时它成为 session leader, group leader

    // 先查看子进程从属于哪个会话
    sid = getsid(getpid());
    printf("sid = %d\n", sid);

    // 让子进程创建新会话
    sid = setsid();
    if (sid < 0) {
      perror("setsid");
    }
    // 查看子进程当前从属于哪个会话
    printf("sid = %d\n", sid);
  }

  while(1) sleep(1);
  return 0;
}
