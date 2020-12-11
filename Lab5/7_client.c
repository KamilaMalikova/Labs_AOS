//7. Осуществить при помощи программ п. 6. обмен сообщениями между несколькими пользователями,
//при условии, что каждому пользователю предназначены сообщения любого или определенного типа (по договоренности).
//Будут ли примеры с очередями сообщений "приводить себя в порядок"?
//Что произойдет, если прервать процесс-сервер с помощью клавиши CTRL-C?


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
#include <mqueue.h>

struct messages{
    long type;
    char text[2];
};

int main (int argc, char ** argv, char * envp[]) {
    key_t key;
    int msg_id_server;
    char * p;
    struct messages *m1, *m2;

    if (argc != 2){
        printf("Usage %s msgid\n", argv[0]);
        exit(1);
    }

    msg_id_server = strtol(argv[1], &p, 10);

    char snum[6];
    sprintf(snum, "%d", getpid());
    char *ms = malloc(strlen("Message from client with pid ") + strlen(snum) + 1);
    strcpy(ms, "Message from client with pid ");
    strcat(ms, snum);

    m1 = malloc(strlen(ms)+5);
    m1->type = getpid();
    strcpy(m1->text, ms);

    //printf("Client:\nType: %ld\n'%s'\n", m1->type, m1->text);
    if(msgsnd(msg_id_server, m1, strlen(ms), 0) == -1){
            perror("msgsnd");
            exit(1);
    }
    free(m1);

    m2 = malloc(100);
    if((l = msgrcv(msg_server, m2, 100, getpid(), MSG_EXCEPT)) == -1){
        perror("msgrcv");
        exit(1);
    }
    printf("Client:\nType: %ld\n%s\n", m2->type, m2->text);
    //printf("'%*s'\n", l, m2->text);
    free(m2);
    exit(0);
}

