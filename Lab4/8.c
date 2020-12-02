//8. Добавить в один из процессов использование слабой блокировки. Что произойдет?

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

struct flock lock;

int main (int argc, char ** argv) {

    if(argc < 2){
        printf("Usage %s filename", argv[0]);
        exit(1);
    }

    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    int fd;

    if(fork()){ // parent
        fd = open(argv[1], O_WRONLY | O_CREAT, 0700);
        lock.l_type = F_WRLCK;
        if(fcntl(fd, F_SETLKW, &lock) == -1){
            perror("write lock");
            exit(errno);
        }
        int i = 0;
        while(i < 1000){
            char str[4];
            sprintf(str, "%d", i);
            write(fd, &str, sizeof(str));
            i++;
        }

        lock.l_type = F_UNLCK;
        if(fcntl(fd, F_SETLKW, &lock) == -1){
            perror("unlock");
            exit(errno);
        }
    }else{ //child
        fd = open(argv[1], O_RDONLY | O_CREAT, 0700);

        int l;
        char buf[20];
        while((l = read(fd, buf, sizeof(buf))) > 0){
            write(1, buf, l);
        }
    }
    exit(0);
}

