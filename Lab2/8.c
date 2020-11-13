//8. Открыть файл (достаточно большого размера), доступный для чтения.
//Имя файла передается из командной строки.
//После открытия файла создать параллельный процесс с помощью только fork.
//В обоих процессах создать свои файлы для записи, читать информацию из общего файла и копировать ее в собственные выходные файлы (не на экран).
//Вывести на экран содержимое полученных файлов из порожденного процесса по окончании записи в файл и из родительского процесса,
//          дождавшись завершения порожденного процесса.
//Посмотреть, что изменится, если читаемую процессами информацию сразу выводить на экран.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char * argv[], char * envp[]){
    if(argc != 2){
        printf("Usage: %s file\n", argv[0]);
        exit(0);
    }
    int fd, fd_p, fd_c;
    fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        perror(argv[1]);
        exit(errno);
    }
    if(fork()){
        //parent
        int l, st;
        char buff[1];
        fd_p = creat("file_8_1", 0600);
        while ((l=read(fd, buff, 1))>0)
            write(fd_p, buff, l);
        close(fd_p);
        wait(&st);
        fd_p = open("file_8_1", O_RDONLY);
        if(fd_p == -1){
            perror("file_8_1");
            exit(1);
        }
        char buff2[4024];
        while((l = read(fd_p, buff2, 4024)) > 0){
            write(1, buff2, l);
        }
        printf("\n");
        close(fd_p);
    }else{
        //child
        fd_c = creat("file_8_2", 0600);
        int l;
        char buff[1];
        char buff2[4024];
        while ((l=read(fd, buff, 1))>0)
            write(fd_c, buff, l);
        close(fd_c);
        fd_c = open("file_8_2", O_RDONLY);
        if(fd_c == -1){
            perror("file_8_2");
            exit(1);
        }

        while((l = read(fd_c, buff2, 4024)) > 0){
            write(1, buff2, l);
        }
        printf("\n");
        close(fd_c);
    }
    close(fd);
    exit(0);
}
