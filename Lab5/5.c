//5. Написать программу, позволяющую удалять очереди сообщений по идентификатору. Обработать возможные ошибочные ситуации.

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

int main (int argc, char ** argv, char * envp[]) {
    int msg_id;
    char * p;

    if(argc != 2){
        printf("Usage: %s msg_id\n", argv[0]);
        exit(1);
    }

    msg_id = strtol(argv[1], &p, 10);
    int l;
    if((l = msgctl(msg_id, IPC_RMID, NULL)) == -1){
        perror("msgctl");
        exit(1);
    }
    exit(0);
}

