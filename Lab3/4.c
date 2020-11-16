//4. Создать длительный параллельный процесс (в порожденном процессе выполнять вложенные циклы,
//каждый на 100 или больше итераций,
//и выводить на экран номер итерации для внешнего цикла).
//Дождаться нормального завершения порожденного процесса.
//Посмотреть, какой статус будет передан в родительский процесс.


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

    if(fork() == 0){
        for(int i = 0; i< 100; i++){
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
    }
}

