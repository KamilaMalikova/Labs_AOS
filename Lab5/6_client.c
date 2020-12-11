//6. Написать программы для работы с очередями сообщений в соответствии с моделью клиент-сервер:
//      каждый процесс использует собственную очередь сообщений.
//Процесс-сервер читает запросы из своей очереди сообщений и посылает ответ процессам-клиентам в их очереди.
//Процессы-клиенты читают ответ и выводят его в выходной поток.
//Процессы-клиенты должны передавать процессу-серверу информацию о своих очередях сообщений (куда записывать ответ).


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
    int msg_id, msg_id_server;
    int msg_type, l;
    char * p;
    struct messages *m1, *m2;

    if (argc != 2){
        printf("Usage %s msgid\n", argv[0]);
        exit(1);
    }
    key = IPC_PRIVATE;

    if((msg_id = msgget(key, IPC_CREAT|0600)) == -1){
        perror("msgget");
        exit(1);
    }

    printf("Msg_id: %d\n", msg_id);
    msg_id_server = strtol(argv[1], &p, 10);

    char snum[6];
    sprintf(snum, "%d", getpid());
    char *ms = malloc(strlen("Message to server from client with pid ") + strlen(snum) + 1);
    strcpy(ms, "Message to server from client with pid ");
    strcat(ms, snum);

    m1 = malloc(strlen(ms)+5);
    m1->type = msg_id;
    strcpy(m1->text, ms);

    //printf("Client:\nType: %ld\n'%s'\n", m1->type, m1->text);
    if(msgsnd(msg_id_server, m1, strlen(ms), 0) == -1){
            perror("msgsnd");
            exit(1);
    }
    free(m1);

    m2 = malloc(100);
    if((l = msgrcv(msg_id, m2, 100, 0, 0)) == -1){
        perror("msgrcv");
        exit(1);
    }
    printf("Client:\nType: %ld\n%s\n", m2->type, m2->text);
    //printf("'%*s'\n", l, m2->text);
    free(m2);
    msgctl(msg_id, IPC_RMID, NULL);
    exit(0);
}

