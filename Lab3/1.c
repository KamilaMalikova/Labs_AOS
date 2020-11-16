//1. Изменить реакцию процесса на некоторый сигнал при помощи signal.
//В функции обработчике переустановить реакцию на сигнал на значение по умолчанию.
//Запустить программу и объяснить наблюдаемый результат.


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
    bool a = true;
    signal(SIGINT, disp);
    while(a){
        printf("Wait .....\n");
        sleep(1);
    }
}
