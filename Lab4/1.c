//1. Создать параллельный процесс, используя только fork.
//Организовать обмен информацией между процессами через каналы.
//Предусмотреть однонаправленную и двунаправленную связь.
//При создании двунаправленной связи исключить возможность появления «смертельных объятий».

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[], char * envp[]){
    int stat;
    int pipe1[2];
    int pipe2[2];

    int data_processed;
    char some_data[] = "123";
    char buffer[80];
    memset(buffer, 0, sizeof(buffer));

    if(pipe(pipe1) == -1){
        perror("Cannot create a pipe\n");
        exit(errno);
    }
    if(pipe(pipe2) == -1){
        perror("Cannot create a pipe\n");
        exit(errno);
    }
    //child
    if(fork() == 0){
        //write to pipe1
        close(pipe1[0]);
        //read from pipe2
        close(pipe2[1]);

        data_processed = read(pipe2[0], buffer, sizeof(buffer));
        printf("Read %d bytes: %s\n", data_processed, buffer);
        char new_data[] = "123456";
        printf("Sending new data: %s\n", new_data);

        data_processed = write(pipe1[1], new_data, strlen(new_data));
        printf("Wrote %d bytes\n", data_processed);

        close(pipe1[1]);
        close(pipe2[0]);
        exit(0);
    } //parent
    else{
        // write to pipe2
        close(pipe2[0]);
        // read from pipe1
        close(pipe1[1]);

        data_processed = write(pipe2[1], some_data, strlen(some_data));
        printf("Wrote %d bytes\n", data_processed);

        data_processed = read(pipe1[0], buffer, sizeof(buffer));
        printf("Read %d bytes: %s\n", data_processed, buffer);

        wait(&stat);
        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }
}

