//11. Написать программу, иллюстрирующую возможность синхронизации процессов при помощи очередей сообщений.

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
    int msg_id, l;
    char *p;
    struct messages *m1, *m2;

    if(argc < 2){
        printf("Usage %s msg_id", argv[0]);
        exit(1);
    }
    msg_id = strtol(argv[1], &p, 10);

    m2 = malloc(100);
    if((l = msgrcv(msg_id, m2, 100, 0, 0)) == -1){
        perror("msgrcv");
        exit(1);
    }
    printf("%d:\nType: %ld\n%s\n", getpid(), m2->type, m2->text);

    char snum[6];
    sprintf(snum, "%d", getpid());
    char *ms = malloc(strlen("Message from client with pid ") + strlen(snum) + 1);
    strcpy(ms, "Message from client with pid ");
    strcat(ms, snum);

    m1 = malloc(strlen(ms)+5);
    m1->type = getpid();
    strcpy(m1->text, ms);
    if(msgsnd(msg_id, m1, strlen(ms), 0) == -1){
            perror("msgsnd");
            exit(1);
    }
    free(m1);
    free(m2);
    exit(0);
}

