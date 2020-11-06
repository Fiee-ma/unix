// myrmdir.c
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  if (rmdir(argv[1]) == -1) {
    perror("rmdir");
    return -1;
  }
  return 0;
}
