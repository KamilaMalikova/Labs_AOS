//10. Написать программу, которая выводит на экран содержимое файла в обратном порядке:
//      сначала выводится последний символ файла,
//      затем предпоследний и так далее до первого.
//Использовать lseek и read.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[], char * envp[]){
    int fd1, fd2, l;
    char buff;
    if(argc != 2){
        printf("Usage: %s file\n", argv[0]);
        exit(1);
    }
    fd1 = open(argv[1], O_RDONLY);
    if(fd1 == -1){
        perror(argv[1]);
        exit(1);
    }

    lseek(fd1, 1*sizeof(char), SEEK_END);
    while((lseek(fd1, -2*sizeof(char), SEEK_CUR)) >=0){
        read(fd1, &buff, sizeof(buff));
        write(1, &buff, sizeof(buff));
    }
    close(fd1);
    exit(0);
}
