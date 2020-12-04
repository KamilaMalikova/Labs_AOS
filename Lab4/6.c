//6. Создать именованный канал (любым способом). Убедиться, что канал создан.
//Рассмотреть особенности работы с именованным каналом (открыть файл с установленным и не установленным флагом O_NDELAY).
//Использовать его для обмена информацией с процессом, созданным другим пользователем (своим соседом).

#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
    int fd, l;
    char buf[50];

    if(argc < 2){
        printf("Usage: %s filename", argv[0]);
        exit(1);
    }

    if ( mkfifo(argv[1], 0777) ) {
        perror("mkfifo");
        exit(0);
    }
    printf("file is created\n");

    if ( (fd = open(argv[1], O_RDONLY)) < 0 ) {
        perror("open");
        remove(argv[1]);
        exit(1);
    }
    printf("%s is opened\n", argv[1]);

    while((l = read(fd, buf, sizeof(buf))) > 0){
        write(1, &buf, l);
    }
    close(fd);
//    remove("fifo");
    exit(0);
}
