//1. Создать очередь сообщений или получить доступ к уже существующей очереди.
//Вывести на экран статистическую информацию об очереди сообщений.
//Поместить несколько сообщений различных типов в очередь.

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
    char text[1];
};

int main (int argc, char ** argv, char * envp[]) {
    key_t key;
    int msg_id;
    struct messages m1;
    struct msqid_ds info;
    struct passwd *p;
    struct group *g;

    if((key = ftok(argv[0], 1)) == -1){
        perror("ftok");
        exit(1);
    }
    if((msg_id = msgget(key, IPC_CREAT|0600)) == -1){
        perror("msgget");
        exit(1);
    }

    m1.type = getpid();
    strcpy(m1.text, "Hello");
    if(msgsnd(msg_id, (void *) &m1, sizeof(m1.text), 0) == -1){
        perror("msgsnd");
        exit(1);
    }
    if(msgrcv(msg_id, (void*) &m1, sizeof(m1.text), getpid(), 0) == -1){
        perror("msgrcv");
        exit(1);
    }
    if(msgctl(msg_id, IPC_STAT, &info) == -1){
        perror("msgget");
        exit(1);
    }
    printf("Key: %d\n", info.msg_perm.__key);
    p = getpwuid(info.msg_perm.uid);
    printf("Owner: %s\n", p->pw_name);
    g = getgrgid(info.msg_perm.gid);
    printf("Groud: %s\n", g->gr_name);
    p = getpwuid(info.msg_perm.cuid);
    printf("Creator: %s\n", p->pw_name);
    g = getgrgid(info.msg_perm.cgid);
    printf("Creator group: %s\n", g->gr_name);
    printf("Permission: 0%o\n", info.msg_perm.mode);
    printf("Last msgsnd time: %s", ctime(&info.msg_stime));
    printf("Last msgrcv time: %s", ctime(&info.msg_rtime));
    printf("Last attribute change time: %s", ctime(&info.msg_ctime));
    printf("Max number of bytes in queue allowed: %ld\n", info.msg_qbytes);
    printf("Number of bytes in queue: %ld\n", info.__msg_cbytes);
    printf("Number of messages in queue: %ld\n", info.msg_qnum);
    printf("PID of last msgsnd time: %d\n", info.msg_lspid);
    printf("PID of last msgrcv time: %d\n", info.msg_lrpid);

    exit(0);
}

