//11. Написать программу, позволяющую использовать sigaction для реализации примера синхронизации процессов.
//Выполнить эту программу и объяснить ее поведение. Использовать sigsuspend и sigprocmask.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

struct sigaction sa;

void disp(int sig){
    printf("\nSignal handler\n");
    sleep(4);
}

int main(int argc, char * argv[], char * envp[]){
    int stat;
    int c_pid;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = disp;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGTSTP);
    //sa.sa_flags = SA_RESETHAND;

    if((c_pid = fork()) == 0){
        sigaction(SIGINT, &sa, NULL);
        for(int i = 0; i< 10000000; i++){
            for(int j = 0; j < 150; j++){
                continue;
            }
            printf("Iteration: %d\n", i);
        }
        exit(3);
    }else{
        sleep(2);
        printf("1");
        kill(c_pid, SIGINT);
        sleep(1);
        printf("2");
        kill(c_pid, SIGINT);
        sleep(1);
        printf("3");
        kill(c_pid, SIGUSR1);
        kill(c_pid, SIGTSTP);
        wait(&stat);
        printf("Return value: %d\n", stat);
        printf("Status: %d\n", WEXITSTATUS(stat));
        if(WIFSIGNALED(stat)){
            printf("Signal: %d\n", WTERMSIG(stat));
        }
        exit(0);
    }


}

