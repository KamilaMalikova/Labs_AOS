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


}
