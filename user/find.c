#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int cmp(const char* p, const char* q){
    int i = 0;
    while (*(p+i) != '\0' && *(q+i) != '\0'){
        if (*(p+i) != *(q+i))
            return 0;
        i++;
    }
    return 1;
}

char* fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void find_and_print(char* path, char* file_name){
    //
    char buff[32], *p;
    struct dirent de;
    struct stat st; 
    int fd;
    fd = open(path, 0);
    fstat(fd, &st);
    switch (st.type){

    case T_DIR:
        strcpy(buff, path);
        p = buff + strlen(buff);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            if (de.name[0] == '.' && de.name[1] == 0)
                continue;
            if (de.name[0] == '.' && de.name[1] == '.' && de.name[2] == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            
            if (stat(buff, &st) < 0){
                continue;
            }
            if (st.type == T_DIR){
                find_and_print(buff, file_name);
            }
            else if (st.type == T_FILE){
                if (!strcmp(de.name, file_name)){
                    printf(buff);
                    printf("\n");
                }
            }
        }
        break;
    }
}

int main(int argc, char* argv[]){
    char* path = argv[1];
    char* file_name = argv[2];
    find_and_print(path, file_name);
    exit(0);
}