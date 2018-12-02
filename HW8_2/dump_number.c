#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv) {
  int n;
  scanf("%d", &n);
  int out = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
  int mbuf[n];
  for (int i = 0; i < n; ++i) {
    scanf("%d", mbuf + i);
  }
  write(out, mbuf, n * 4);
  close(out);
  return 0;
}
