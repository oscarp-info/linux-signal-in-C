/*
 * en otra terminal realizar un login con otro usuario (ejemplo: prueba)
 * enviar un kill -SIGINT <pid>
 * verificar que no se tiene permisos
 *
 * == -sh: 4: kill: Operation not permitted ==
 */
#include <stdio.h>
#include <unistd.h> // sleep
#include <stdlib.h> // EXIT_FAILURE
#include <signal.h>
#include <string.h>

void handler(int signal_number);

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handler;
    if (sigaction(SIGINT, &sa, NULL) != 0)
    {
        perror("signal()");
    }

    fprintf(stderr, "main:: pause()...\n");

    pause();

    fprintf(stderr, "main:: end\n");

    return 0;
}

void handler(int signal_number)
{
    fprintf(stderr, "handler:: caught signal %d\n", signal_number);
    return;
}
