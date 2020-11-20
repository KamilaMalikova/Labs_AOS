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
    printf("\nSignal handler\n\n");
}

int main(int argc, char * argv[], char * envp[]){
    int stat;
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    sigset_t mask2;
    sigemptyset(&mask2);
    sigaddset(&mask2, SIGUSR1);

    raise(SIGUSR2);

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = disp;
    sigaction(SIGUSR2, &sa, NULL);

    int c_pid;
    //child
    if((c_pid = fork()) == 0){
        sigsuspend(&mask2);
        printf("Got signal. My pid is %d\n", getpid());
        int fd = open("file11", O_RDONLY);
        int buff_size = 1;
        char buff[buff_size];
        int l;
        while((l = read(fd, buff, buff_size)) > 0){
            write(1, buff, buff_size);
        }
        close(fd);
        printf("\n");
        kill(getppid(), SIGUSR2);
        printf("Signaled to %d\n", getppid());
        printf("Bye\n");
        exit(0);
    }//parent
    else{
        int fd = creat("file11", 0777);
        int l;
        int buff_size = 1;
        char buff[buff_size];
        while((l = read(0, buff, buff_size)) > 0){
            write(fd, buff, buff_size);
            if(buff[0] == '\n'){
                break;
            }
        }
        close(fd);
        kill(c_pid, SIGUSR2);
        printf("Signaled to %d\n", c_pid);
        sigsuspend(&mask2);
        printf("Got signal from my son\nBye\n");
        wait(&stat);
        exit(0);
    }
}

