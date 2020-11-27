//5. С помощью системных вызовов pipe и dup реализовать конвейер: who | wc -l.

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) {

    int fd[2];
    pipe(fd);

    if(fork() == 0){ // who process
        char *argv[] = { "who", NULL };
        dup2 (fd[1], 1);
        close (fd[0]);
        execvp (argv[0], argv);
    }
    if(fork() == 0){ // wc process
        char *argv[] = { "wc", "-l", NULL };
        dup2(fd[0], 0);
        close(fd[1]);
        execvp(argv[0], argv);
    }

  close (fd[0]);
  close (fd[1]);

  return 0;

}
