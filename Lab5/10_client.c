//10. Еще раз модифицировать эти программы так, чтобы использовалась только одна очередь сообщений и для запросов к серверу, и для всех ответов.


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

#define MSG_EXCEPT 020000

struct messages{
    long type;
    char text[2];
};

int main (int argc, char ** argv, char * envp[]) {
    key_t key;
    int msg_id_server, l;
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

    if(msgsnd(msg_id_server, m1, strlen(ms), 0) == -1){
            perror("msgsnd");
            exit(1);
    }
    free(m1);

    m2 = malloc(100);
    if((l = msgrcv(msg_id_server, m2, 100, 1, 0)) == -1){
        perror("msgrcv");
        exit(1);
    }
    printf("%d: Type: %ld   %s\n", getpid(), m2->type, m2->text);
    //printf("'%*s'\n", l, m2->text);
    free(m2);
    exit(0);
}

