//7. Модифицировать программу, включив в нее setpgrp в порожденный процесс до того, как он будет выполнять pause.
//Повлияет ли на порожденный процесс нажатие клавиши прерывания в тот момент, когда родительский процесс "спит"?
//Будет ли показан порожденный процесс в выводе команды ps?

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
        setpgrp();
        printf("I am son. Pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgrp());
        pause();
        printf("Look at my pid. Pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgrp());
        system("ps -l");
        exit(0);
    }else{
        printf("I am father. Pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgrp());
        pause();
        printf("Bye. My pid: %d\n", getpid());
        exit(0);
    }
}
