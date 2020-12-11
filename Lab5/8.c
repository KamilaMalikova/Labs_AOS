//8. Модифицировать программы п. 6 так, чтобы они завершались корректно и в случае прерывания по CTRL-C.



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

int msg_id;

struct messages{
    long type;
    char text[2];
};

void hangler(int sig){
    msgctl(msg_id, IPC_RMID, NULL);
    printf("Message queue is deleted\n");
    exit(0);
}

int main (int argc, char ** argv, char * envp[]) {
    key_t key;
    int msg_type, l;
    char * p;
    struct messages *m1, *m2;

    signal(SIGINT, hangler);
    if((key = ftok(argv[0], 1)) == -1){
        perror("ftok");
        exit(1);
    }

    if((msg_id = msgget(key, IPC_CREAT|0600)) == -1){
        perror("msgget");
        exit(1);
    }
    printf("Msg_id: %d\n", msg_id);
    while(1){
       m1 = malloc(100);
        if((l = msgrcv(msg_id, m1, 100, 0, 0)) == -1){
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
        m2->type = msg_id;
        strcpy(m2->text, ms);
        //printf("Server:\n   Type: %ld\n     %s", m2->type, m2->text);
        //printf("'%s'\n", m2->text);

        if(msgsnd(m1->type, m2, strlen(ms), 0) == -1){
            perror("msgsnd");
            exit(1);
        }
        free(m1);
    }
    exit(0);
}

