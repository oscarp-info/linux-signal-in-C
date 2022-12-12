/*
 * compilar:    gcc -Wall signal_06.c -o s
 * presionar Ctrl-C para que se ejecute el handler por default y termine verificando la espera de la señal por pause()
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
        perror("signal() SIGKILL");
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
