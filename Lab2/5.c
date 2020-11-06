//5. Изменить программу п. 3 так, чтобы родительский процесс выполнялся, не ожидая завершения порожденного процесса.
//Что произойдет с порожденным процессом, когда он завершится? Как убить зомби?

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char * argv[], char * envp[]){
    int status, c_pid;
    if ((c_pid = fork()) == 0){
        printf("I am son. Pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgrp());
        sleep(2);
        printf("Look at my pid. Pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgrp());
        system("ps -l");
        exit(0);
    }else{
        printf("I am father. Pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgrp());
        printf("Bye. My pid: %d\n", getpid());
        exit(0);
    }
}
