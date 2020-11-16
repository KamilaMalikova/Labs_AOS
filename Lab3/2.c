//2. Модифицировать программу п.1 так, чтобы вместо signal использовать sigaction.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

struct sigaction sa;

void disp(int sig){
    printf("\nDisposition is changed\n");
}

int main(int argc, char * argv[], char * envp[]){
    bool a = true;

    sa.sa_handler = disp;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESETHAND;
    sigaction(SIGINT, &sa, NULL);
    while(a){
        printf("Wait .....\n");
        sleep(1);
    }
}
