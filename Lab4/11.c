//11. Повторить выполнение п. 10, включив в процессы для синхронизации работы с терминалом использование режима слабой блокировки.
//Как изменится поведение процессов?

#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

struct flock lock;

int main (int argc, char ** argv) {
    int fd[2];
    char buf;
    lock.l_type = F_WRLCK;

    if(fork() == 0){//child
        close(fd[1]);
        close(0);
        fcntl(fd[0], F_SETLKW, lock);
        while(read(fd[0], &buf, sizeof(buf))){
            write(1, &buf, sizeof(buf));
        }
        exit(0);
    }else{//parent
        close(1);
        close(fd[0]);
        fcntl(fd[1], F_SETLKW, lock);
        while(read(0, &buf, sizeof(buf))){
            write(fd[1], &buf, sizeof(buf));
            if(buf == '\n') break;
        }
        exit(0);
    }
}
