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
#include <time.h>
#include <sys/sysmacros.h>
#include <pwd.h>

int main(int argc, char * argv[], char * envp[]){
    struct stat st;
    struct passwd *pswd;
    int fd, ret;
    if(argc != 2){
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    if((stat(argv[1], &st)) == -1){
        perror(argv[1]);
        exit(1);
    }
    //File type
    if(S_ISREG(st.st_mode)) printf("%s is a regular file\n", argv[1]); // is it a regular file?
    else if (S_ISDIR(st.st_mode)) printf("%s is a directory\n", argv[1]);
    else if(S_ISCHR(st.st_mode)) printf("%s is a character device\n", argv[1]);
    else if(S_ISBLK(st.st_mode)) printf("%s is a block device\n", argv[1]);
    else if(S_ISFIFO(st.st_mode)) printf("%s is a FIFO", argv[1]);
    printf("File permissions: ");
    printf( (st.st_mode & S_IRUSR) ? "r" : "-");
    printf( (st.st_mode & S_IWUSR) ? "w" : "-");
    printf( (st.st_mode & S_IXUSR) ? "x" : "-");
    printf( (st.st_mode & S_IRGRP) ? "r" : "-");
    printf( (st.st_mode & S_IWGRP) ? "w" : "-");
    printf( (st.st_mode & S_IXGRP) ? "x" : "-");
    printf( (st.st_mode & S_IROTH) ? "r" : "-");
    printf( (st.st_mode & S_IWOTH) ? "w" : "-");
    printf( (st.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    printf("Inode: %lud\n", st.st_ino);
    printf("Major: %ud\n", major(st.st_rdev));
    printf("Minor: %ud\n", minor(st.st_rdev));

    pswd = getpwuid(st.st_uid);
    fd = open(argv[1]);

    printf("UID: %d - %s, ", st.st_uid, pswd->pw_name);
    printf("GID: %d - %s\n", st.st_gid, getpwuid(st.st_gid)->pw_name);
    printf("Real size: %d", lseek(fd, 1, SEEK_END));
    printf("Device: %lud \n", st.st_dev);
    printf("Links: %lud \n", st.st_nlink);
    printf("Size=%ld bytes\n", st.st_size);
    printf("Size of block: %ld\nBlocks: %ld\n", st.st_blksize, st.st_blocks);
    printf("Last access: %s", ctime(&st.st_atime));
    printf("Last modification: %s", ctime(&st.st_mtime));
    printf("Last status change: %s", ctime(&st.st_ctime));
    exit(0);
}

