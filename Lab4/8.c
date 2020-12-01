//8. Добавить в один из процессов использование слабой блокировки. Что произойдет?

#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>


int main (int argc, char ** argv) {
    int fd, len;
    char buf[10];
    if(argc < 2 ){
        printf("Usage: %s filename", argv[0]);
        exit(1);
    }

    if ( mkfifo(argv[1], 0777) ) {
        perror("mkfifo");
        exit(0);
    }
    printf("file is created\n");

    if(fork() == 0){//child
        if ( (fd = open(argv[1], O_WRONLY|O_NDELAY)) <= 0 ) {
            perror("open to write");
            printf("Error %d\n", errno);
            remove(argv[1]);
            exit(errno);
        }
        char new_data[] = "0123456789";
        int data_len = write(fd, &new_data, strlen(new_data));
        printf("\nWritten %d bytes\n", data_len);
        close(fd);
        exit(0);
    }else{//parent
        //sleep(1);
        if ((fd = open(argv[1], O_RDONLY)) <= 0 ) {
            perror("open to read");
            remove(argv[1]);
            exit(1);
        }
        printf("read\n");
        int data_len;
        while((data_len = read(fd, &buf, sizeof(buf))) > 0){
            write(1, &buf, sizeof(buf));
        }
        close(fd);
        remove(argv[1]);
        printf("closed\n");
        exit(0);
    }
}
