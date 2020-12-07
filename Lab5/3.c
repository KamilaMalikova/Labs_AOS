//3. Модифицировать программу п. 2, позволив ей избежать ожидания в случае отсутствия в очереди сообщений данного типа.


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
    int msg_id;
    int msg_type;
    char * p;
    struct messages *m1;

    if(argc != 3){
        printf("Usage: %s msg_id msg_type\n", argv[0]);
        exit(1);
    }

    msg_id = strtol(argv[1], &p, 10);
    msg_type = strtol(argv[2], &p, 10);
    int l;
    if((l = msgrcv(msg_id, m1, 20, msg_type, IPC_NOWAIT)) == -1){
        perror("msgrcv");
        exit(1);
    }
    printf("Type: %ld\n", m1->type);
    printf("'%*s'\n", l, m1->text);
    exit(0);
}

