#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h> // pause

void handler(int signal_number)
{
    switch (signal_number)
    {
    case SIGINT:
        printf("INT(%d)\n", signal_number);
        break;

    case SIGALRM:
        printf("ALRM(%d)\n", signal_number);
        break;
    default:
        break;
    }
}

int main()
{

    struct sigaction sa1, sa2;

    memset(&sa1, 0, sizeof(struct sigaction));
    sa1.sa_handler = &handler;
    sa1.sa_flags = SA_NODEFER; // don't block the signal when it's handler is running
    sigaction(SIGINT, &sa1, NULL);

    memset(&sa2, 0, sizeof(struct sigaction));
    sa2.sa_handler = &handler;
    sa2.sa_flags = SA_NODEFER; // don't block the signal when it's handler is running
    sigaction(SIGALRM, &sa2, NULL);

    while (1)
    {
        // Establecemos una alarma para dentro de un segundo
        alarm(1);
        // Pausamos la ejecución del programa para que
        // se quede esperando a recibir una señal.
        // cuidado, que si no ponemos pause, alarm se esta setenado todo el tiempo
        // y no llega a llamarse al handler....
        pause();
    }

    return 0;
}
