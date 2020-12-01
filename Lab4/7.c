//7. Создать два параллельных процесса, в каждом из которых осуществляется работа с одним и тем же файлом.
//Каждый процесс открывает файл (имя файла передается через список аргументов командной строки).
//Один процесс пишет в файл, другой - читает из него.
//Что произойдет без включения блокировок?

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
    int fd, l;
    char buf[10];

    struct flock lock;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;


    if(argc < 2 ){
        printf("Usage: %s filename", argv[0]);
        exit(1);
    }

    if((fd = creat(argv[1], 0700)) == -1){
        perror("creat");
        exit(1);
    }
    close(fd);
    if(fork() == 0){//child
        if ((fd = open(argv[1], O_RDWR)) < 0 ) {
            perror("open to write");
            exit(errno);
        }
        lock.l_type = F_WRLCK;
        if(fcntl(fd, F_SETLKW, &lock)<0){
            perror("lock");
            exit(errno);
        }
        printf("\nReady to write...\n");
        int i = 0;
        int j = 1000;
         while(i <= 1000){
            char str[4];
            l = read(fd, &i, 5);
            i++;
            printf("%d\n", i);
            sprintf(str, "%d", i);
            lseek(fd, 0, SEEK_SET);
            write(fd, &str, l);
        }
        lock.l_type = F_UNLCK;
        if(fcntl(fd, F_SETLKW, &lock)<0){
            perror("unlock");
            exit(errno);
        }
        close(fd);
        exit(0);
    }else if(fork() == 0){//child
        if ((fd = open(argv[1], O_RDWR)) < 0 ) {
            perror("open to write");
            exit(errno);
        }
        lock.l_type = F_WRLCK;
        if(fcntl(fd, F_SETLKW, &lock)<0){
            perror("lock");
            exit(errno);
        }
        printf("\nReady to write...\n");
        int i = 0;
        while(i <= 1000){
            char str[4];
            l = read(fd, &i, 5);
            i++;
            printf("%d\n", i);
            sprintf(str, "%d", i);
            lseek(fd, 0, SEEK_SET);
            write(fd, &str, l);
        }
        lock.l_type = F_UNLCK;
        if(fcntl(fd, F_SETLKW, &lock)<0){
            perror("unlock");
            exit(errno);
        }
        close(fd);
        exit(0);
    }
    else{//parent
        if ((fd = open(argv[1], O_RDONLY)) < 0 ) {
            perror("open to read");
            exit(errno);
        }
        printf("Ready to read...\n");
        while((l = read(fd, &buf, sizeof(buf))) != 0){
            write(1, buf, l);
        }

        close(fd);
        wait(NULL);
        exit(0);
    }
}
x
