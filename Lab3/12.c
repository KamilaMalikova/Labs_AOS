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
}

int main(int argc, char * argv[], char * envp[]){
    sigset_t myset;
    (void) sigemptyset(&myset);
    while (1) {
        (void) printf("I'm running, waiting for a signal...\n");
        (void) sigsuspend(&myset);
    }
}

