//4. Повторить п. 2, создавая параллельные процессы с помощью связки fork - exec. Как передать дескрипторы канала в порожденный процесс?

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char* argv[]) {

    int fd[2];
    char buff;
    pipe(fd);
    if(fork() != 0) { //parent
        close(fd[1]); // close write
        int fd1 = creat("ps", 0777);
        int l;
        while((l = read(fd[0],&buff,sizeof(buff))) > 0)  {
            write(fd1, &buff, l);
        }
    } else { //son
        dup2(fd[1],1); //standart output write to pipe
        close(fd[0]);
        close(fd[1]);
        execlp("ps","-l",NULL);
}
 return 0;

}
