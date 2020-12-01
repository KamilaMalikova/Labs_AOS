//10. Создать два параллельных процесса, разделяющие ввод с клавиатуры и вывод на экран.
//Что получится при исполнении этих процессов?

#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>


int main (int argc, char ** argv) {
    int fd[2];
    char buf;
    if(fork() == 0){//child
        close(fd[1]);
        close(0);
        while(read(fd[0], &buf, sizeof(buf))){
            //write(1, &buf, sizeof(buf));
        }
        exit(0);
    }else{//parent
        //dup2(fd[1], 1);
        close(1);
        close(fd[0]);
        while(read(0, &buf, sizeof(buf))){
            write(fd[1], &buf, sizeof(buf));
            if(buf == '\n') break;
        }
        exit(0);
    }
}
