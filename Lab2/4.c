//4. Изменить программу п. 3 так, чтобы родительский процесс завершился раньше порожденного.
//Какой процесс становится родительским для порожденного после того,
//как исходный родительский процесс завершился?

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
        sleep(3);
        printf("Look at my pid. Pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgrp());
        exit(0);
    }else{
        printf("I am father. Pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgrp());
        sleep(1);
        printf("Bye. My pid: %d\n", getpid());
        exit(0);
    }
}
