//3. Написать программу, в которой процесс порождает новый и позволяет порожденному процессу завершиться.
//Оба процесса должны выводить свои идентификаторы (процесса, родительского процесса, группы процессов).
//Проверить идентификатор и статус завершения порожденного процесса.
//Выполнить данную программу и посмотреть ее результаты.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char * argv[], char * envp[]){
    int status, c_pid;
    if ((c_pid = fork()) == 0){
        printf("I am son. Pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgrp());
        exit(3);
    }else{
        printf("I am father. Pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgrp());
        printf("Wait for my son with pid %d....\n", c_pid);
        if(wait(&status) == c_pid)
            printf("Son's exit status: %d\n", WEXITSTATUS(status));
        exit(0);
    }
}
