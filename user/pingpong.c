#include "kernel/types.h"
#include "user/user.h"

int main() {
  int p1[2], p2[2];
  pipe(p1);
  pipe(p2);

  int pid = fork();
  if (pid == 0) {
    // Filho
    char buf;
    read(p1[0], &buf, 1);
    printf("%d: received ping\n", getpid());
    write(p2[1], &buf, 1);
    exit(0);
  } else {
    // Pai
    char c = 'a';
    write(p1[1], &c, 1);
    wait(0);
    read(p2[0], &c, 1);
    printf("%d: received pong\n", getpid());
    exit(0);
  }
}
