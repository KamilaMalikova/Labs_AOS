//7. Написать программу для получения справочной информации о файлах с помощью системного вызова stat.
//      Имя файла передается в программу из командной строки.
//Получить справочную информацию для различных типов файлов
//    (обычный файл, каталог, специальные байт- и блок-ориентированные файлы).
// изучить inode (где старшие и младшие номер какие поля)
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char * argv[], char * envp[]){
    struct stat st;
    int fd, ret;
    if(argc != 2){
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    if((stat(argv[1], &st)) == -1){
        perror(argv[1]);
        exit(1);
    }
    printf("Device=%lld Inode=%d Mode=0%o\n", st.st_dev, st.st_ino, st.st_mode);
    printf("Links=%d UID=%d GID=%d\n", st.st_nlink, st.st_uid, st.st_gid);
    printf("TypeDevice=0x%llx | %lld Size=%d\n", st.st_rdev, st.st_rdev, st.st_size);
    printf("Size of block=%d Count of blocks=%d\n", st.st_blksize, st.st_blocks);
    printf("atime=%s", ctime(&st.st_atime));
    printf("mtime=%s", ctime(&st.st_mtime));
    printf("ctime=%s", ctime(&st.st_ctime));
    exit(0);
}

