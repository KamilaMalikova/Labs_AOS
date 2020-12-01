//3. Модифицировать программу п. 2 таким образом, чтобы процессы реализовали двунаправленную связь (диалог).

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
    int pipe2[2];
    int l;
    char buff[50];
    if(pipe(pipe1) == -1){
        perror("Cannot create a pipe\n");
        exit(errno);
    }
    if(pipe(pipe2) == -1){
        perror("Cannot create a pipe\n");
        exit(errno);
    }
    //child
    if(fork() == 0){
        close(pipe1[0]);
        close(pipe2[1]);
        while((l = read(0, buff, sizeof(buff))) > 0){
            write(pipe1[1], buff, l);
        }
        close(pipe1[1]);
        while((l = read(pipe2[0], buff, sizeof(buff))) > 0){
            write(1, buff, l);
        }
        printf("Close .....\n");
        close(pipe2[0]);
        exit(0);
    } //parent
    else{
        // read from pipe1
        close(pipe1[1]);
        close(pipe2[0]);
        while((l = read(pipe1[0], buff, sizeof(buff))) > 0){
            write(1, buff, l);
        }
        close(pipe1[0]);
        printf("Parent writes...\n");
        while((l = read(0, buff, sizeof(buff))) > 0){
            write(pipe2[1], buff, l);
        }
        close(pipe2[1]);
        printf("\nI closed a pipe\n");
        wait(&stat);
        exit(0);
    }
}

