#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>


struct messages{
    long type;
    char text[5];
};

int main (int argc, char ** argv, char * envp[]) {
    int msg_id;
    int msg_type;
    char * p;
    struct messages * m1;

    if(argc < 3){
        printf("Usage: %s msg_id msg_type\n", argv[0]);
        exit(1);
    }

    msg_id = strtol(argv[1], &p, 10);
    msg_type = strtol(argv[2], &p, 10);

    m1->type = msg_type;
    strcpy(m1->text, "Hello");
    if(msgsnd(msg_id, m1, sizeof(m1->text), 0) == -1){
        perror("msgsnd");
        exit(1);
    }
    printf("Type: %ld\nMessage: %s\n", m1->type, m1->text);
    exit(0);
}

