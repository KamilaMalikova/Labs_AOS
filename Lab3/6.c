//6. Повторить выполнение п. 5 задания, изменив сигнал, посылаемый в порожденный процесс. Что изменится?

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
        for(int i = 0; i< 100; i++){
            for(int j = 0; j < 150; j++){
                continue;
            }
            printf("Iteration: %d\n", i);
        }
        exit(3);
    }else{
        kill(c_pid, SIGTERM);
        wait(&stat);
        printf("Return value: %d\n", stat);
        printf("Status: %d\n", WEXITSTATUS(stat));
    }
}

