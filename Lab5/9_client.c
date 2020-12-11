//9. Модифицировать программы п. 6 так, чтобы использовались две очереди:
//  одна для запросов к серверу и одна для всех ответов от сервера к любому клиенту.

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
    key_t key;
    int msg_id_rcv, msg_id_snd;
    int msg_type, l;
    char * p;
    struct messages *m1, *m2;

    if (argc != 3){
        printf("Usage %s msgid_read msgid_wrt\n", argv[0]);
        exit(1);
    }

    msg_id_rcv = strtol(argv[1], &p, 10);
    msg_id_snd = strtol(argv[2], &p, 10);

    char snum[6];
    sprintf(snum, "%d", getpid());
    char *ms = malloc(strlen("Message to server from client with pid ") + strlen(snum) + 1);
    strcpy(ms, "Message to server from client with pid ");
    strcat(ms, snum);

    m1 = malloc(strlen(ms)+5);
    m1->type = getpid();
    strcpy(m1->text, ms);

    //printf("Client:\nType: %ld\n'%s'\n", m1->type, m1->text);
    if(msgsnd(msg_id_snd, m1, strlen(ms), 0) == -1){
            perror("msgsnd");
            exit(1);
    }
    free(m1);

    m2 = malloc(100);
    if((l = msgrcv(msg_id_rcv, m2, 100, 0, 0)) == -1){
        perror("msgrcv");
        exit(1);
    }
    printf("Client:\nType: %ld\n%s\n", m2->type, m2->text);
    //printf("'%*s'\n", l, m2->text);
    free(m2);
    exit(0);
}

