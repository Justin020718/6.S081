#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char*argv[])
{
    // fprintf(1, "hello world!\n");
    if (argc <= 1){
        fprintf(2, "Error! Missing a sleeping time!\n");
        exit(1);
    }
    else{
        //fprintf(1, argv[1]);
        sleep(atoi(argv[1]));
        exit(0);
    }
    //exit(0);
}