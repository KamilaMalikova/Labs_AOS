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
#include <sys/types.h>
#include <sys/wait.h>



int main (int argc, char ** argv) {
    char * prefix;
    int l;
    char buf[10];
    int fd;

    if((fd = open("file", O_RDWR|O_CREAT, 0700)) == -1){
        perror("open");
        exit(1);
    }
    if(fork() == 0){//child
        prefix = "Son:";
    }else{//parent
        prefix = "Father:";
    }
    struct flock lock;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_type = F_WRLCK;
    if(fcntl(fd, F_SETLKW, &lock) == -1){
        perror("lock");
        exit(1);
    }
    while((l = read(0, buf, sizeof(buf)-1)) > 0){
        buf[l] = '\0';
        printf("%s %s", prefix, buf);
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    wait(NULL);
    exit(0);
}
