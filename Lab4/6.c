//6. Создать именованный канал (любым способом). Убедиться, что канал создан.
//Рассмотреть особенности работы с именованным каналом (открыть файл с установленным и не установленным флагом O_NDELAY).
//Использовать его для обмена информацией с процессом, созданным другим пользователем (своим соседом).


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
    int res = mkfifo("fifo", 0777);
    if (res == 0){
       int fd = open("fifo", O_WRONLY);
       if (fd == -1){
            perror("File");
       }
       close(fd);
    }

    exit(0);
}
