//1. Написать программу, которая выполняет некоторый системный вызов,
//например open, и затем выводит возвращаемую ошибку.
//Использовать в программе разные способы вывода сообщения об ошибке:
//      вывод значения errno,
//      вывод соответствующего сообщения из системного массива сообщений об ошибках sys_errlist[],
//      вызов библиотечной функции perror.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[], char * envp[]){
    int file, w;
    char text[20];
    file = open("1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0500);
    printf("file=%d\n", file);
    if(file>=0){
        scanf("%s", text);
        printf("%s\n", text);
        w = write(file, &text, 20);
        if(w < 0){
            printf("errno=%d", errno);
            perror("File write error");
        }
    }else{
        printf("errno=%d\n", errno);
        perror("File creat error");
        printf("sys_errlist:%s \n",sys_errlist[errno]);
    }
        close(file);
        exit(0);
}
