//2. Модифицировать программу п. 1 таким образом, чтобы родительский процесс читал из канала в цикле, пока не встретится конец файла
//      (порожденный процесс может записывать в канал информацию, читаемую им из стандартного входного потока).
//Как избежать бесконечного ожидания родительским процессом чтения из пустого канала?


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char * argv[], char * envp[]){
    int stat;
    int pipe1[2];


    int data_processed;

    if(pipe(pipe1) == -1){
        perror("Cannot create a pipe\n");
        exit(errno);
    }
    //child
    if(fork() == 0){
        //write to pipe1
        close(pipe1[0]);

        char new_data[] = "123456";
        printf("Sending new data: %s\n", new_data);
        data_processed = write(pipe1[1], new_data, strlen(new_data));
        printf("Wrote %d bytes\n", data_processed);
        sleep(5);
        close(pipe1[1]);
        exit(0);
    } //parent
    else{
        // read from pipe1
        close(pipe1[1]);

        fcntl(pipe1[0], F_SETFL, O_NONBLOCK);
        char buff = '\0';
        int l;
        while((l = read(pipe1[0], &buff, sizeof(buff)))){
            if(l == -1 && buff == '\0') continue;
            if(l == -1 && buff != '\0') break;
            write(1, &buff, sizeof(buff));

        }
        printf("\nPipe is empty\n");
        close(pipe1[0]);
        wait(&stat);
        exit(0);
    }
}

