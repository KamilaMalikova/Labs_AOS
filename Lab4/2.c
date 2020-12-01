//2. Модифицировать программу п. 1 таким образом, чтобы родительский процесс читал из канала в цикле, пока не встретится конец файла
//      (порожденный процесс может записывать в канал информацию, читаемую им из стандартного входного потока).
//Как избежать бесконечного ожидания родительским процессом чтения из пустого канала?


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char * argv[], char * envp[]){
    int stat;
    int pipe1[2];
    int l;
    char buff[50];

    if(pipe(pipe1) == -1){
        perror("Cannot create a pipe\n");
        exit(errno);
    }
    //child
    if(fork() == 0){
        close(pipe1[0]);
        while((l = read(0, buff, sizeof(buff))) > 0){
            write(pipe1[1], buff, l);
        }
        close(pipe1[1]);
        exit(0);
    } //parent
    else{
        // read from pipe1
        close(pipe1[1]);
        while((l = read(pipe1[0], buff, sizeof(buff))) != 0){
            write(1, buff, l);
        }
        printf("\nPipe is empty\n");
        close(pipe1[0]);
        wait(&stat);
        exit(0);
    }
}

