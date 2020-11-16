//8. Включить в порожденный процесс системный вызов signal,
//      переопределяющий стандартную реакцию на сигнал (для внешнего цикла установить в функции максимальное значение параметра цикла).
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
}

int main(int argc, char * argv[], char * envp[]){
    int stat;
    int c_pid;
    signal(SIGUSR1, disp);
    if((c_pid = fork()) == 0){
         for(int i = 0; i< 1000; i++){
            for(int j = 0; j < 150; j++){
                continue;
            }
            printf("Iteration: %d\n", i);
        }
        exit(3);
    }else{
        kill(c_pid, SIGUSR1);
        wait(&stat);
        printf("Return value: %d\n", stat);
        printf("Status: %d\n", WEXITSTATUS(stat));

        exit(0);
    }
}

