//7. Повторить выполнение предыдущих пунктов задания, используя в порожденном процессе вместо вложенных циклов системный вызов pause.
//Что изменится?
//Как завершить процесс в случае выполнения с pause п. 4?

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

int main(int argc, char * argv[], char * envp[]){
    int stat;
    int c_pid;
     if((c_pid = fork()) == 0){
        pause();
        exit(3);
    }else{
        kill(c_pid, SIGUSR1);
        wait(&stat);
        printf("Return value: %d\n", stat);
        printf("Status: %d\n", WEXITSTATUS(stat));
        exit(0);
    }
}

