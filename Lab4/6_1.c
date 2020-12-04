//6. Создать именованный канал (любым способом). Убедиться, что канал создан.
//Рассмотреть особенности работы с именованным каналом (открыть файл с установленным и не установленным флагом O_NDELAY).
//Использовать его для обмена информацией с процессом, созданным другим пользователем (своим соседом).

#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main (int argc, char ** argv) {
    int fd, l;
    char buf[50];

    if(argc < 2){
        printf("Usage: %s filename", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_WRONLY)) < 0 ) {
        perror("open");
        remove(argv[1]);
        exit(1);
    }
    printf("%s is opened\n", argv[1]);

    while((l = read(0, buf, sizeof(buf))) > 0){
        write(fd, &buf, l);
    }
    close(fd);
    remove(argv[1]);
    exit(0);
}
