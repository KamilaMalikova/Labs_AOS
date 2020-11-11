//1. Написать программу, которая добавляет новые строки в среду процесса.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

extern int errno;
extern char ** environ;

int main(int argc, char * argv[], char * envp[]){
    int i;
    if(putenv("AAA=I am a new environment param") != 0){
        perror("ENV");
    }
    for (i=0; envp[i]; i++)
        printf("%s\n", envp[i]);
    printf("\nAfter add with environ\n");
    for (i=0; environ[i]; i++)
        printf("%s\n", environ[i]);
    printf("\nNew env param: %s\n", getenv("AAA"));
    exit(0);
}
