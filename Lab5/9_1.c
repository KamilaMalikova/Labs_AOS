
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct messages{
    long type;
    char text[2];
};

int main (int argc, char ** argv, char * envp[]) {
    if(argc < 3){
        printf("Usage %s file msg_id msg_id\n", argv[0]);
        exit(1);
    }
    for(int i = 0; i < 5; i++){
        if(fork() == 0)
            execl(argv[1], argv[1], argv[2], argv[3], NULL);
    }
    exit(0);
}

