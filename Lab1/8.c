//8. Написать программу копирования одного файла в другой.
//      Имена файлов задаются в командной строке
//          (первый аргумент - исходный файл,
//            второй - результирующий).
//Если аргументы командной строки отсутствуют, использовать стандартный ввод и стандартный вывод.
//Копирование файлов выполнить с помощью функции.

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
    if(argc == 1){
        fd1 = 0;
        fd2 = 1;

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
    while ((l=read(fd1, buff, 4096))>0)
        write(fd2, buff, l);


    close(fd1);
    close(fd2);
    exit(0);
}
