#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

extern int errno;

int main(int argc, char * argv[], char * envp[]){
        int i;
        printf("argc=%d\n", argc);
        for (i=0; i<argc; i++)
                printf("argv[%d]=%s\n", i, argv[i]);

        /*
        int i;
        for (i=0; envp[i]; i++)
                printf("%s\n", envp[i]);*/
        exit(0);
}
