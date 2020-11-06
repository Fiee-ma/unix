// hellothread.c

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

// 线程入口函数
void* th_fn(void *arg) {
  char* name = (char*)arg;
  int i;

  for (i = 1; i <= 10; ++i) {
    printf("%s : %d\n", name, i);
    // 判断是 Allen 还是 Luffy
    if (strcmp("Allen", name) == 0)
      usleep(1000*10); // 10 ms
    else
      usleep(1000*5); // 5ms
  }

  return NULL;
}


int main() {
  int err;
  pthread_t allen, luffy;
  char *name1 = "Allen";
  char *name2 = "Luffy";

  // 创建 allen 线程。
  err = pthread_create(&allen, NULL, th_fn, (void*)name1);
  if (err != 0) {
    perror("pthread_create");
    return -1;
  }
  // 创建 luffy 线程
  err = pthread_create(&luffy, NULL, th_fn, (void*)name2);
  if (err != 0) {
    perror("pthread_create");
    return -1;
  }

  // 问题：如果没有此行，会发生什么？
  //sleep(3);

  // 打印线程 id 号
  printf("Allen id: %lx\n", allen);
  printf("Luffy id: %lx\n", luffy);

  return 0;
}
