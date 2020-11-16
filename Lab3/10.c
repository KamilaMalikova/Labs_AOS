//10. Написать программу, иллюстрирующую способ блокирования дополнительных сигналов на время работы обработчика сигнала.
//Что произойдет, если во время обработки некоторого сигнала в процесс поступит несколько однотипных заблокированных сигналов.

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
    sleep(1);
}

int main(int argc, char * argv[], char * envp[]){
    int stat;
    int c_pid;

    sa.sa_handler = disp;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaddset(&sa.sa_mask, SIGTSTP);
    //sa.sa_flags = SA_RESETHAND;
    sigaction(SIGUSR1, &sa, NULL);
    if((c_pid = fork()) == 0){
        for(int i = 0; i< 10000000; i++){
            for(int j = 0; j < 150; j++){
                continue;
            }
            printf("Iteration: %d\n", i);
        }
        exit(3);
    }else{
        kill(c_pid, SIGUSR1);
        kill(c_pid, SIGINT);
        kill(c_pid, SIGTSTP);
        kill(c_pid, SIGUSR1);
        wait(&stat);
        printf("Return value: %d\n", stat);
        printf("Status: %d\n", WEXITSTATUS(stat));
        exit(0);
    }


}

