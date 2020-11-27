#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int fifo[2]; /* 0 - read, 1 - write */

void func1 (void)
{
    char *argv[] = { "/bin/who", NULL };

    dup2 (fifo[1], STDOUT_FILENO);
    close (fifo[0]);
    execvp (argv[0], argv);
}

void func2 (void){
    char *argv[] = { "/bin/wc", "-l", NULL };

    dup2 (fifo[0], STDIN_FILENO);
    close (fifo[1]);
    execvp (argv[0], argv);
}

int main (void)
{
  if (pipe (fifo))
    perror ("pipe");

  if (fork() == 0)
    func1 ();
  if (fork() == 0)
    func2 ();

  close (fifo[0]);
  close (fifo[1]);

  return 0;
}
