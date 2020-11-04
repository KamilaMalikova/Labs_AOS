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

int main(int argc, char * argv[], char * envp[]){
    int fd1, fd2, l;
    char file1;
    char file2;
    char buff[1024];
    if(argc != 3){
        printf("Usage: %s file filecopy\n", argv[0]);
        exit(1);
    }
    fd1 = open(argv[1], O_RDONLY);
    if(fd1 == -1){
        perror(fd1);
        exit(1);
    }
    fd2 = creat(argv[2], 0777);
    if(fd2 == -1){
        perror(fd1);
        exit(1);
    }
    fd1 = dup2(fd1, 0);
    fd2 = dup(fd2, 1);
    while ((l=read(fd1, buff, sizeof(buff)))>0)
        write(fd2, buff, l);

    close(fd1);
    close(fd2);
    exit(0);
}
