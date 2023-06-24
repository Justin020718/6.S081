#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "math.h"
# define RANGE 35

int get_length(char str[])
{
	char *p = str;
	int count = 0;
	while (*p++ != '\0')
	{
		count++;
	}
	return count;
}

int is_prime(char n){
    int num = n;
    for (int i = 2; i <= num/2; ++i ){
        if (num % i == 0){
            return 0;
        }
        
    }
    return 1;
}

char* eliminate(int n, char* a){
    if (get_length(a) == 1){
        a[0] = '\0';
    }
    int j = 0;
    int len = get_length(a);
    // printf("size of a is %d\n",len);
    for (int i = 0; i < len; ++i){
        if ((int)(a[i]) % n != 0 && (int)(a[i] != 0)){
            a[j] = a[i];
            j = j + 1;
        }
    }
    for (int i = j; i < len; i++){
        a[i] = 0;
    }
    // printf("len = %d, after elimination: ", len);
    // for (int i = 0; i < len; i++)
    //     printf("%d ",(int)*(a+i));
    // printf("\n");
    return a;
}

void print_and_fork(char* buff){
    if (get_length(buff) == 0){
        exit(0);
    }
    int p[2];
    int n;

    for (int i = 0;i < get_length(buff); ++i){
        if (is_prime(buff[i]) == 1){
            fprintf(1, "prime %d\n", (int)(buff[i]));

            buff = eliminate((int)(buff[i]), buff);

            // fprintf(1, "fork!\n");

            pipe(p);
            n = fork();
            if (n == 0){
                // child proc
                char buff1[RANGE];
                read(p[0], buff1, get_length(buff) + 1);
                close(p[1]);
                close(p[0]);
                if (get_length(buff) > 0)
                    print_and_fork(buff);
                exit(0);
            }
            else{
                // parent proc
                write(p[1], buff, get_length(buff) + 1);
                close(p[1]);
                close(p[0]);
                int signal;
                wait(&signal);
                exit(0);
            }
        }
    }
}

int main(int argc, char* argv[]){
    char buff[RANGE];
    for (int i = 0; i < RANGE-1;++i)
        buff[i] = (char)(i + 2);
    buff[RANGE - 1] = '\0';
    // for (int i = 0; i<sizeof(buff); i++)
    //     printf("%d \n",(int)*(buff+i));
    print_and_fork(buff);
    exit(0);
}