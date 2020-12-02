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
#include <sys/types.h>
#include <sys/wait.h>



int main (int argc, char ** argv) {

    int l;
    char buf[10];
    if(fork() == 0){//child
        while((l = read(0, buf, sizeof(buf)-1)) > 0){
            printf("Son: %s", buf);
        }
        exit(0);
    }else{//parent
        while((l = read(0, buf, sizeof(buf)-1)) > 0){
            printf("Father: %s", buf);
        }
        wait(NULL);
        exit(0);
    }
}
