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
#include <string.h>

struct sigaction sa;



void print_sigset_t(sigset_t *set)
{
    int x = 0;
    for(int i = 1; i < 32; i++){
        if (sigismember(set, i)) printf("x = %d ", i);
        //if (sigismember(set, 2)) printf("x = %d ", 2);
        //if (sigismember(set, 12)) printf("x = %d ", 12);
    }
//    printf("x = %d ", x);
	printf("\n");
}


void disp(int sig){
    printf("\%d Signal handler\n", sig);
    sigset_t set;
    sigpending(&set);
    print_sigset_t(&set);
    sleep(4);
}


int main(int argc, char * argv[], char * envp[]){
    int stat;
    int c_pid;
    sigset_t set;

    memset(&sa, 0, sizeof(sa));
    //memset(&set, 0, sizeof(set));
    sa.sa_handler = disp;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    sa.sa_mask = set;
    sigaction(SIGINT, &sa, NULL);

    sigaction(SIGUSR1, &sa, NULL);

    if((c_pid = fork()) == 0){
        for(int i = 0; i< 15; i++){
            sleep(1);
            printf("Iteration: %d\n", i);
        }
        exit(3);
    }else{
        sleep(1);
        printf("1\n");
        kill(c_pid, SIGINT);
        //sleep(1);
        printf("2\n");
        kill(c_pid, SIGUSR1);
        printf("3\n");
        kill(c_pid, SIGUSR1);
        kill(c_pid, SIGUSR2);


        wait(&stat);
        printf("Return value: %d\n", stat);
        printf("Status: %d\n", WEXITSTATUS(stat));
        if(WIFSIGNALED(stat)){
            printf("Signal: %d\n", WTERMSIG(stat));
        }
        exit(0);
    }
}



