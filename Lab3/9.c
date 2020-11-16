//9. Включить в порожденный процесс вместо системного вызова kill системный вызов alarm с перехватом и без перехвата сигнала.
//Что изменится?

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

void disp(int sig){
    signal(sig, SIG_DFL);
    printf("\nDisposition is changed\n");
    sleep(1);
}

int main(int argc, char * argv[], char * envp[]){
    int stat;
    int c_pid;
    //signal(SIGALRM, disp);
    if((c_pid = fork()) == 0){
        alarm(1);
         for(int i = 0; i< 10000000; i++){
            for(int j = 0; j < 150; j++){
                continue;
            }
            printf("Iteration: %d\n", i);
        }
        exit(3);
    }else{
        wait(&stat);
        printf("Return value: %d\n", stat);
        printf("Status: %d\n", WEXITSTATUS(stat));

        exit(0);
    }
}

