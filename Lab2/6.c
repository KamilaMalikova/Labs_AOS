//6. Изменить программу п. 3 так, чтобы оба процесса выполняли системный вызов pause после вывода идентификаторов.
//Запустить программу в фоновом режиме и посмотрите (с помощью ps), какие процессы существуют для данного пользователя.
//Выполнить kill -9 pid для родительского процесса.
//Что произойдет с порожденным?
//После очистки текущего сеанса, вновь выполнить программу, но уже в интерактивном режиме.
//Нажать на терминале клавишу CTRL-C. Что произойдет с родительским и порожденным процессами?
//Можно ли получить такой же результат, если нажать клавишу прерывания после того, как родительский процесс завершится?

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

void disp(int sig){
    return;
}

int main(int argc, char * argv[], char * envp[]){
    int status, c_pid;
    signal(SIGUSR1, disp);
    if ((c_pid = fork()) == 0){
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
