// ejecutar desde otra consola kill -KILL <pid>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// prototipo para el handler de la señal
void handler(int signal_number);

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handler;
    sigaction(SIGINT, &sa, NULL);

    pid_t pid;

    pid = getpid();
    printf("pid=%d\n", pid);

    while (1)
        sleep(2);

    return 0;
}

void handler(int signal_number)
{
    fprintf(stderr, "SIGINT recibida '%s'!\n", strsignal(signal_number));
    return;
}