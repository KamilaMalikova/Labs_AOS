//6. Модифицировать программу п. 4 для создания разреженного файла.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[], char * envp[]){
    int fd, ret;
    if(argc != 2){
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }else{
        fd = creat(argv[1], 0600);
        if(fd == -1){
           perror(argv[1]);
           exit(1);
        }
        write(fd, "1", 1);
        lseek(fd, 2000000, SEEK_SET);
        write(fd, "1", 1);
        close(fd);
    }
    exit(0);
}
