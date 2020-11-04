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

int main(int argc, char * argv[], char * envp[]){
    int fd1, fd2, l;
    char file1;
    char file2;
    char buff[1024];
    if(argc > 3 || argc < 1){
        printf("Usage: %s file filecopy\n", argv[0]);
        exit(1);
    }
    if(argc == 1){
        printf("File 1: ");
        scanf("%s", file1);
        printf("File 2: ");
        scanf("%s", file2);
    }
    else if(argc == 2){
        file1 = argv[1];
        printf("File 2: ");
        scanf("%s", file2);
    }else{
        file1 = argv[1];
        file2 = argv[2];
    }

    fd1 = open(argv[1], O_RDONLY);
    if(fd1 == -1){
        perror(fd1);
        exit(1);
    }
    fd2 = creat(argv[2], 0777);
    if(fd1 == -1){
        perror(fd1);
        exit(1);
    }

    while ((l=read(fd1, buff, sizeof(buff)))>0)
        write(fd2, buff, l);

    close(fd1);
    close(fd2);
    exit(0);
}
