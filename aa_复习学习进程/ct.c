// ct.c
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig) {
  if (sig == SIGHUP) {
    int fd = open("tmp", O_WRONLY | O_CREAT, 0664);
    write(fd, "hello SIGHUP\n", 32);
    exit(0);
  }
}

void print() {
  pid_t pid, sid, pgid, tpgid;

  pid = getpid();
  sid = getsid(pid);
  pgid = getpgid(pid);
  tpgid = tcgetpgrp(0);
  if (tpgid < 0) {
    perror("tcgetpgrp");
  }

  printf("pid = %d, pgid = %d, sid = %d, tpgid = %d\n", pid, pgid, sid, tpgid);
}
int main(int argc, char* argv[]) {
  signal(SIGHUP, handler);

  // 打印当前进程 id，组 id，会话 id，当前会话中的前台进程组 id.
  print();

  // 将前台进程组设置为 bash 进程组的 id.
  tcsetpgrp(0, getppid());

  print();

  while(1) sleep(1);
  return 0;
}
