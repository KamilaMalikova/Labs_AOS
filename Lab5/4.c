//4. Модифицировать программу п. 2, позволив ей принимать первые несколько байтов сообщений произвольных размеров.


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
    int text;
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
    m1 = malloc(4096);
    int l;
    if((l = msgrcv(msg_id, m1, 2, msg_type, MSG_NOERROR)) == -1){
        perror("msgrcv");
        exit(1);
    }
    printf("%d\n", l);
    printf("Type: %ld\n", m1->type);
    printf("'%d'\n", m1->text);
    free(m1);
    exit(0);
}

