/*
 * ejemplo con sigaction, instalo el handler int y bloquea la señal usr1 mientras el handler esta en running....
 * ejecutar el programa y desde otra consola enviar la signal SIGUSR1
 * verificar que la señal es recibida
 * luego, apretar ctrl-c para que entre al handler
 * hay un loop para simular que se quede corriendo
 * en ese momento desde otra consola enviar la signal SIGUSR1
 * y verificar que se encola (el handler no recibe la señal)
 * al terminar el loop de int, la señal encolada se procesa
 *
 */

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void handler_int(int signal_number);
void handler_usr1(int signal_number);

int main()
{
    pid_t pid;
    struct sigaction sa, sa_usr1;
    sigset_t set;

    // instalo el handler usr1
    memset(&sa_usr1, 0, sizeof(sa_usr1));
    sa_usr1.sa_handler = &handler_usr1;
    sigaction(SIGUSR1, &sa_usr1, NULL);

    // instalo el handler int y bloquea la señal usr1 mientras el handler esta en running....
    memset(&sa, 0, sizeof(sa));
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sa.sa_mask = set;
    sa.sa_flags = 0;
    sa.sa_handler = &handler_int;
    sigaction(SIGINT, &sa, NULL);

    pid = getpid();
    printf("pid=%d\n", pid);

    while (1)
    {
        sleep(2);
    }

    return 0;
}

void handler_int(int signal_number)
{

    int i = 5;
    while (i)
    {
        fprintf(stderr, "SIGINT running!\n");
        sleep(3);
        i--;
    }

    return;
}

void handler_usr1(int signal_number)
{
    fprintf(stderr, "SIGUSR1 recibida!\n");
    return;
}