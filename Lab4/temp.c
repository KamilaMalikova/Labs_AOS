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


int main (int argc, char ** argv){
    int fd, l;

    struct flock lock;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_type = F_WRLCK;
    int c_pid1 = fork();
    int c_pid2 = fork();


    if(c_pid1 == 0){
        if ((fd = open(argv[1], O_RDWR)) < 0 ) {
            perror("open to write");
            exit(errno);
        }

        if(fcntl(fd, F_SETLKW, &lock) == -1){
            perror("lock");
            exit(1);
        }
        int i = 0;
        while(i < 1000){
            l = read(fd, &i, 4);
            if(l == -1){
                perror("read");
                exit(1);
            }
            i++;
            printf("%d\n", i);
            lseek(fd, 0, SEEK_SET);
            char str[4];
            sprintf(str, "%d", i);
            write(fd, &str, l);
        }
        close(fd);
        exit(0);
    }else if(c_pid2 == 0){
        if ((fd = open(argv[1], O_RDWR)) < 0 ) {
            perror("open to write");
            exit(errno);
        }
    //    lock.l_type = F_WRLCK;
        if(fcntl(fd, F_SETLKW, &lock) == -1){
            perror("lock");
            exit(1);
        }
        int i = 0;
        while(i < 1000){
            l = read(fd, &i, 4);
            if(l == -1){
                perror("read");
                exit(1);
            }
            i++;
            printf("%d\n", i);
            lseek(fd, 0, SEEK_SET);
            char str[4];
            sprintf(str, "%d", i);
            write(fd, &str, l);
        }
        close(fd);
        exit(0);
    }else{

    }
}
