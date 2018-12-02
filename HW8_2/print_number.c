#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv) {
  int in = open(argv[1], O_RDONLY);
  int cur;
  while (read(in, &cur, 4) != 0) {
    printf("%d ", cur);
  }
  puts("");
  close(in);
  return 0;
}
