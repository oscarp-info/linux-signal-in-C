
/*
 * SIGKILL no se puede cambiar el handler
 * gcc -Wall sigkill.c -o sigkill
 *  kill -SIGKILL <pid>
 *  kill -9 <pid>
 *
 *
 */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int signal_number)
{
    printf("SIGKILL recived!\n");
}

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handler;
    if (sigaction(SIGKILL, &sa, NULL) != 0)
    {
        perror("signal() SIGKILL");
    }

    pid_t pid;

    pid = getpid();
    fprintf(stderr, "pid=%d\n", pid);

    while (1)
        sleep(2);

    return 0;
}
