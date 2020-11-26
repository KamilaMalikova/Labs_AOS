//3. Модифицировать программу п. 2 таким образом, чтобы процессы реализовали двунаправленную связь (диалог).


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

struct flock lock;

int main(int argc, char * argv[], char * envp[]){
    int stat;
    int pipe1[2];
    int pipe2[2];
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    int data_processed;

    if(pipe(pipe1) == -1){
        perror("Cannot create a pipe\n");
        exit(errno);
    }

        if(pipe(pipe2) == -1){
        close(pipe1[0]);
        close(pipe1[1]);
        perror("Cannot create a pipe\n");
        exit(errno);
    }
    //child
    if(fork() == 0){
        //write to pipe1
        close(pipe1[0]);
        //read from pipe2
        close(pipe2[1]);

        char new_data[] = "123456";
        printf("Sending new data: %s\n", new_data);
        data_processed = write(pipe1[1], new_data, strlen(new_data));
        printf("Wrote %d bytes\n", data_processed);

        fcntl(pipe2[0], F_SETFL, O_NONBLOCK);
        char buff = '\0';
        int l;
        while((l = read(pipe2[0], &buff, sizeof(buff)))){
            if(l == -1 && buff == '\0') continue;
            if(l == -1 && buff != '\0') break;
            write(1, &buff, sizeof(buff));
        }
        printf("\nPipe is empty\n");
        close(pipe1[1]);
        close(pipe2[0]);
        exit(0);
    } //parent
    else{
        // read from pipe1
        close(pipe1[1]);
        //write to pipe2
        close(pipe2[0]);
        fcntl(pipe1[0], F_SETFL, O_NONBLOCK);
        char buff = '\0';
        int l;
        while((l = read(pipe1[0], &buff, sizeof(buff)))){
            if(l == -1 && buff == '\0') continue;
            if(l == -1 && buff != '\0') break;
            write(1, &buff, sizeof(buff));
        }
        printf("\nPipe is empty\n");
        char new_data[] = "789";
        printf("Sending new data: %s\n", new_data);
        data_processed = write(pipe2[1], new_data, strlen(new_data));
        printf("Wrote %d bytes\n", data_processed);
        sleep(2);

        close(pipe1[0]);
        close(pipe2[1]);
        wait(&stat);
        exit(0);
    }
}

