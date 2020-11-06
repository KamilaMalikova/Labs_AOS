//2. Кто выполняется первым после fork: отец или сын?
//Написать программу, которую можно использовать для проверки данной ситуации.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[], char * envp[]){
    if (fork() == 0){
        printf("I am son.\n");
        exit(0);
    }else{
        printf("I am father.\n");
        exit(0);
    }
}
