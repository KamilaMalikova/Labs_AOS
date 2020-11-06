//11. Выполнить из программы на Си какую-либо команду Shell (cp или ls):
//      с помощью вызовов fork-exec,
//      с помощью библиотечной функции system.
//Необходимые для команды данные передать через аргументы командной строки.


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char * argv[], char * envp[]){
    if(argc == 1){
        printf("Usage: %s command params....\n", argv[0]);
        exit(1);
    }
    if(fork()){
        //parent
        int st;
        wait(&st);

    }else{
        //child
        int ex = execvp(argv[1], argv+1);
        if(ex == -1){
            perror("Execution error");
        }
    }
    exit(0);
}
