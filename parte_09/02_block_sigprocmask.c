/*
 * ejemplo para bloquear temporalmente con sigprocmask
 * ejecutar el programa y verificar que la señal int esta bloqueada Ctrl-C
 * comentar la linea sigprocmask(SIG_BLOCK, &set, NULL);
 * y verificar que ya no esta bloqueada
 *
 *
 */

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int signal_number);

int main()
{
    pid_t pid;
    struct sigaction sa;
    sigset_t set;

    // configuro la mascara para INT (para bloquear/desbloquear)
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    // instalo el handler para INT
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handler;
    sigaction(SIGINT, &sa, NULL);

    pid = getpid();
    printf("pid=%d\n", pid);

    while (1)
    {
        printf("Ingreso a la zona critica\n");
        sigprocmask(SIG_BLOCK, &set, NULL);
        fprintf(stderr, "SIGINT bloqueada\n");
        // .....
        sleep(5);

        printf("Salgo a la zona critica\n");
        sigprocmask(SIG_UNBLOCK, &set, NULL);
        fprintf(stderr, "SIGINT desbloqueada\n");
        sleep(5);
        // ....
    }

    return 0;
}

void handler(int signal_number)
{
    fprintf(stderr, "== SIGINT señal recibida............! == \n");
    return;
}
