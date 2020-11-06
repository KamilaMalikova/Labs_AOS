//5. Повторно выполнить программу п. 4;
//проверить результаты выполнения каждого системного вызова.
//Объяснить полученные результаты.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[], char * envp[]){
    int fd, ret;
    char buff[4];
    char buff_all[200];
    if(argc != 2){
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }else{
        fd = open(argv[1], O_RDWR);

        if(fd == -1){
           perror("Cannot open file");
           exit(1);
        }
        // read from the begining
        ret = lseek(fd, 0*sizeof(char), SEEK_SET);
        if(ret == -1){
           perror("Cannot lseek in file");
           exit(1);
        }
        ret = read(fd, &buff, sizeof(buff));
        printf("buff = %s \n", buff);
        // current position
        ret = lseek(fd, 0*sizeof(char), SEEK_CUR);
        ret = read(fd, &buff, sizeof(buff));
        printf("buff = %s \n", buff);

        ret = lseek(fd, (-3)*sizeof(char), SEEK_END);
        ret = read(fd, &buff, sizeof(buff));
        if(ret == -1){
           perror("Cannot read from file");
           exit(1);
        }
        printf("buff = %s \n", buff);

        //Write
        ret = lseek(fd, 0*sizeof(char), SEEK_SET);
        if(ret == -1){
           perror("Cannot lseek in file");
           exit(1);
        }
        char write_buff[] = {'s', 't','a','r', 't'};
        ret = write(fd, write_buff, sizeof(write_buff));
        // current position
        char write_buff2[] = {'c', 'u','r','r', 'e', 'n', 't'};
        ret = lseek(fd, 1*sizeof(char), SEEK_CUR);
        ret = write(fd, write_buff2, sizeof(write_buff2));

        char write_buff3[] = {'e', 'n','d'};
        ret = lseek(fd, (0)*sizeof(char), SEEK_END);
        ret = write(fd, write_buff3, sizeof(write_buff3));

        ret = lseek(fd, 0*sizeof(char), SEEK_SET);
        ret = read(fd, &buff_all, sizeof(buff_all));
        printf("buff_all = %s \n", buff_all);
        close(fd);
    }
    exit(0);
}



