//9. Изменить программу п. 8 таким образом, чтобы функция копирования
//использовала стандартные ввод и вывод,
//а вызывающая программа переназначала стандартные ввод и вывод на указанные в аргументах командной строки файлы.
// пользова dup

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[], char * envp[]){
    int fd1, fd2, l;
    char buff[4096];
    if(argc != 3){
        printf("Usage: %s file1 file2\n", argv[0]);
        exit(1);

    }else{
        fd1 = open(argv[1], O_RDONLY);
        if(fd1 == -1){
            perror(argv[1]);
            exit(1);
        }
        fd2 = creat(argv[2], 0777);
        if(fd1 == -1){
            perror(argv[2]);
            exit(1);
        }
    }

    dup2(fd1, 0);
    dup2(fd2, 1);
    while ((l=read(0, buff, 4096))>0)
        write(1, buff, l);


    close(fd1);
    close(fd2);
    exit(0);
}
