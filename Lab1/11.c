//11. Написать программу, которая определяет, какой файл из перечисленных в командной строке имеет наибольшую длину.
//Вывести длину файла в байтах.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char * argv[], char * envp[]){
    struct stat st;
    int  i, size = -1, max_file;
    if(argc < 2){
        printf("Usage: %s file1 file2 ....\n", argv[0]);
        exit(1);
    }
    for(i = 1; i < argc; i++){
        if((stat(argv[i], &st)) == 0){
            if(st.st_size > size){
                size = st.st_size;
                max_file = i;
            }
        }else{
            perror(argv[i]);
        }
    }

    if(size != -1){
        printf("%s is a file with max size %d\n", argv[max_file], size);
    }
    exit(0);
}
