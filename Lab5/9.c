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
#include <signal.h>

int msg_id_snd, msg_id_rcv;

struct messages{
    long type;
    char text[2];
};

void hangler(int sig){
    msgctl(msg_id_snd, IPC_RMID, NULL);
    msgctl(msg_id_rcv, IPC_RMID, NULL);
    printf("Message queue is deleted\n");
    exit(0);
}

int main (int argc, char ** argv, char * envp[]) {
    key_t key_snd, key_rcv;
    int msg_type, l;
    char * p;
    struct messages *m1, *m2;

    signal(SIGINT, hangler);
    if((key_snd = ftok(argv[0], 'S')) == -1){
        perror("ftok");
        exit(1);
    }
    if((key_rcv = ftok(argv[0], 'R')) == -1){
        perror("ftok");
        exit(1);
    }
    if((msg_id_snd = msgget(key_snd, IPC_CREAT|0600)) == -1){
        perror("msgget");
        exit(1);
    }
    if((msg_id_rcv = msgget(key_rcv, IPC_CREAT|0600)) == -1){
        perror("msgget");
        exit(1);
    }
    printf("Msg to write: %d\nMsg to read: %d\n", msg_id_rcv, msg_id_snd);
    while(1){
       m1 = malloc(100);
        if((l = msgrcv(msg_id_rcv, m1, 100, 0, 0)) == -1){
            perror("msgrcv");
            exit(1);
        }
        printf("Server:\nType: %ld\n%s\n", m1->type, m1->text);
        //printf("'%*s'\n", l, m1->text);

        char snum[50];
        sprintf(snum, "%ld", m1->type);
        char *ms = malloc(strlen("Message from server to client's queue ") + strlen(snum) + 1);
        strcpy(ms, "Message from server to client's queue ");
        strcat(ms, snum);

        m2 = malloc(strlen(ms)+5);
        m2->type = msg_id_rcv;
        strcpy(m2->text, ms);

        if(msgsnd(msg_id_snd, m2, strlen(ms), 0) == -1){
            perror("msgsnd");
            exit(1);
        }
        free(m1);
        free(m2);
    }
    exit(0);
}

