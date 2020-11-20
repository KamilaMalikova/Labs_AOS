//3. Написать программу, исключающую появление зомби для завершающихся порожденных процессов.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

struct sigaction sa;

void disp(int sig){
    printf("\nDisposition is changed\n");
}

int main(int argc, char * argv[], char * envp[]){

/*    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NOCLDWAIT;
    sigaction(SIGCHLD, &sa, NULL);
  */
    signal(SIGCHLD, SIG_IGN);
    for(int i = 0; i < 6; i++){
        if(fork() == 0){

            printf("Child: %d, Parent: %d\n", getpid(), getppid());
            sleep(1);
            printf("Child: %d, Parent: %d\n", getpid(), getppid());
            exit(0);
        }
    }

    printf("Parent: %d\n", getpid());
    //sleep(3);
    system("ps -l");
    exit(0);

}
