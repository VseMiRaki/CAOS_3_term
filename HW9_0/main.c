#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

int main(){
  char file_name[PATH_MAX];
  uint64_t result = 0;
  struct stat st;
  char * nl;
  while(fgets(file_name, sizeof(file_name), stdin)){
    nl = memchr(file_name, '\n', sizeof(file_name));
    if(nl){
      *nl = '\0';
    }
    if(lstat(file_name, &st)!=-1){
      if(S_ISREG(st.st_mode)){
        result += st.st_size;
      }
    }
  }
  printf("%" PRIu64"\n", result);
}
