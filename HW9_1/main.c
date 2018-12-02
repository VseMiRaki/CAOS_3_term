#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
size_t my_read(int fd, char *buf, size_t bytesToRead) {
  for (size_t bytesRead = 0; bytesRead < bytesToRead;) {
    ssize_t currentRead = read(fd, buf + bytesRead, bytesToRead - bytesRead);
    if (currentRead == -1) {
      return 10000000;
    }
    if (currentRead == 0) {
      return bytesRead;
    }
    bytesRead += currentRead;
  }
  return bytesToRead;
}

int main() {
  char file_name[PATH_MAX];
  struct stat st;
  char *nl;
  while (fgets(file_name, sizeof(file_name), stdin)) {
    nl = memchr(file_name, '\n', sizeof(file_name));
    if (nl) {
      *nl = '\0';
    }
    if (stat(file_name, &st) != -1) {
      if (!(st.st_mode & S_IXUSR))
        continue;
      int file = open(file_name, O_RDONLY);
      if (file == -1) {
        continue;
      }
      char buf[4];
      size_t read = my_read(file, buf, 4);
      if (read == 10000000) {
        close(file);
        return 1;
      }
      if (buf[0] == 0x7f && buf[1] == 0x45 && buf[2] == 0x4c &&
          buf[3] == 0x46 && (st.st_mode & S_IXUSR)) {
        close(file);
        continue;
      } else {
        close(file);
        file = open(file_name, O_RDONLY);
        if (file == -1) {
          continue;
        }
        char buf[PATH_MAX];
        read = my_read(file, buf, 2);
        if (read == 10000000) {
          close(file);
          continue;
        }
        if (buf[0] != '#' || buf[1] != '!') {
          printf("%s", file_name);
          close(file);
          continue;
        }
        read = my_read(file, buf, PATH_MAX);
        if (read == 10000000) {
          close(file);
          continue;
        }
        nl = memchr(buf, '\n', sizeof(buf));
        if (nl) {
          *nl = '\0';
        }
        if (!(lstat(buf, &st) != -1 && st.st_mode & S_IXUSR)) {
          printf("%s", file_name);
          close(file);
        }
      }
    }
  }
}
