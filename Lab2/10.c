//10. Создать (с помощью связки fork - exec) параллельный процесс.
//Имя исполняемого файла для exec передается с помощью аргумента командной строки.
//Передать в порожденный процесс некоторую информацию через список параметров (список аргументов в функции main).
//Каждый процесс (и родительский, и порожденный) должен вывести на экран список переданных ему аргументов и свое окружение.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char * argv[], char * envp[]){
    if(argc == 1){
        printf("Usage: %s prog params....\n", argv[0]);
        exit(1);
    }
    if(fork()){
        //parent
        for(int i =0; i< argc; i++){
            printf("%s ",argv[i]);
        }
        printf("\nEnvironment\n");
        for (int i=0; envp[i]; i++)
            printf("%s\n", envp[i]);
    }else{
        //child
        int ex = execv(argv[1], argv+1);
        if(ex == -1){
            perror("Execution error");
        }
    }
    exit(0);
}
