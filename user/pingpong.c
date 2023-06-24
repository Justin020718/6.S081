#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char*argv[])
{
    int p[2]; //p[0] is the reading endian, whild p[1] is the writing endian.
    int n;
    pipe(p);
    n = fork();
    if (n != 0){
        char buf1[10];
        int status;
        int pid = getpid();
        // main proc
        write(p[1], "ping\n", 5);
        read(p[0], buf1, sizeof(buf1));
        wait(&status);
        fprintf(1, "%d: received pong\n",pid);
    }
    else{
        char buf2[10];
        int pid = getpid();
        // child proc
        write(p[1], "pong\n", 5);
        read(p[0], buf2, sizeof(buf2));
        fprintf(1, "%d: received ping\n",pid);
        exit(0);
    }
    close(p[0]);
    close(p[1]);
    exit(0);
}