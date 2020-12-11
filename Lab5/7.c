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
#include <signal.h>

#define MSG_EXCEPT 020000

int msg_id;

struct messages{
    long type;
    char text[2];
};

void handler(int sig){
    msgctl(msg_id, IPC_RMID, NULL);
    exit(0);
}

int main (int argc, char ** argv, char * envp[]) {
    key_t key;
    int msg_type, l;
    char * p;
    struct messages *m1, *m2;
    signal(SIGINT, handler);
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
        if((l = msgrcv(msg_id, m1, 100, getpid(), MSG_EXCEPT)) == -1){
            perror("msgrcv");
            exit(1);
        }
        printf("%d:\nType: %ld\n%s\n", getpid(), m1->type, m1->text);

        m2 = malloc(sizeof(m1->text)+8);
        m2->type = getpid();
        strcpy(m2->text, m1->text);

        if(msgsnd(m1->type, m2, strlen(m2->text), 0) == -1){
            perror("msgsnd");
            exit(1);
        }
        free(m1);
        free(m2);
    }

    exit(0);
}

