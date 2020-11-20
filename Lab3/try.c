#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* заводим отдельные функции для родителя и потомка - так удобнее смотреть */
void parent(pid_t childID);
void child(pid_t parentID);

/* единая маска для нашего сигнала - для синхронизации должно быть достаточно SIGUSR1 */
sigset_t maskusr1;

/* Наш пустой обработчик сигнала */
void signal_handler(int sig) {
    return;
}

/* Блокируем прием сигнала процессом */
void lock_signal(void) {
    sigprocmask(SIG_BLOCK, &maskusr1, NULL);
}

/* Разблокируем прием сигнала процессом */
void unlock_signal(void) {
    sigprocmask(SIG_UNBLOCK, &maskusr1, NULL);
}

/* Старт здесь */
int main(int argc, char *argv[]) {
    struct sigaction sa;
    pid_t pID;

    /* Формируем маску, состояющую из одного сигнала и сразу говорим процессу, что сигнал заблокирован,
    а значит все посылы этого сигнала нам, должны ожидать доставки (pending) */
    sigemptyset(&maskusr1);
    sigaddset(&maskusr1, SIGUSR1);
    lock_signal();

    /* Устанавливаем обработку сигнала */
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigaction(SIGUSR1, &sa, NULL);

    /* Размножаемся */
    pID = fork();
    /* Проверяем кто мы и идем в соотв. функцию */
    /* При этом передаем идент. процесса-соседа */
    if (pID < 0) {
        printf("fork() errorno = %d\n", errno);
        return 1;
    } else if (pID > 0) {
        parent(pID);
    } else {
        child(getppid());
    }

    return 0;
}

/* Родитель */
void parent(pid_t childID) {
    int i, res, sig;
    printf("Hi! I'm parent with PID = %d (my child is %d)\n", getpid(), childID);

    for (i = 0; i < 1; i++) {
        res = i * sqrt(16);
        printf("parent result = %i\n", res);
        kill(childID, SIGUSR1);
        printf("parent waits\n");
        unlock_signal();
        sigwait(&maskusr1, &sig);
        lock_signal();
    }
    printf("Parent finished\n");
}

/* Потомок */
void child(pid_t parentID) {
    int i, res, sig;
    printf("Hi! I'm child width PID = %d (my parent is %d)\n", getpid(), parentID);

    for (i = 0; i < 1; i++) {
        res = i * 10 + 124 + 98 * i;
        printf("child result = %i\n", res);
        kill(parentID, SIGUSR1);
        printf("child waits\n");
        unlock_signal(); /* Разблокировали получение сигнала */
        sigwait(&maskusr1, &sig); /* Дождались получения */
        lock_signal(); /* Снова заблокировали получение сигнала */
    }
    printf("Child finished\n");
}
