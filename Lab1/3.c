//3. Повторно выполнить программу п. 2 с теми же исходными данными;
//проверить результаты выполнения каждого системного вызова.
//Объяснить полученные результаты.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[], char * envp[]){
    int file, file2, file3, r;
    int p;
    char * ptr;
    char buf[1024];
    if(argc != 3){
        printf("Usage: %s filename rights\n", argv[0]);
        exit(1);
    }
    p=strtol(argv[2], &ptr, 8);
    if(strlen(argv[2])!=ptr-argv[2]){
        fprintf(stderr, "%s: incorrect filemode\n", argv[2]);
        exit(1);
    }else{
        umask(0000);
        //Создать новый файл
        file = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, p);
        if(file >=0){
           int l;
           char text[20];
           //записать в него несколько строк,
           if((l = write(file, "Helloween", 10)) < 0){
                perror("1.Cannot write to file");
           }else{
                printf("1.Data is written to file\n");
                //закрыть
                close(file);
           }
        }else{
            perror("1.Unable to open the file");
        }
        //повторно открыть файл на чтение
        file2 = open(argv[1], O_RDONLY);
        if(file2 >= 0){
        //прочитать из него информацию
            r = read(file2, buf, 10);
            if(r == -1){
                perror("2.Cannot read from file ");
            }else{
                //вывести ее на экран,
                printf("2.Read from file: %s \n", buf);
            }
            //закрыть.
            close(file2);
        }else{
            perror("Cannot open file ");
        }
        file3 = open(argv[1], O_RDWR);
        if(file >= 0){
            printf("3.File is reopened and closed again\n");
            close(file3);
        }else{
            perror("3.Cannot open file with flag O_RDWR");
        }
    }
    exit(0);
}

