/*
 * Cuando apretamos Ctrl-Z
 * en realidad le estamos enviando una señal a nuestro proceso
 * lo que queremos hacer es cambiar lo que hace el handler por default, que
 * es terminar nuestro programa
 *
 * si comentamos esta linea:
 * sigaction(SIGTSTP, &sa, NULL);
 * y apretamos Crtl-Z el programa sigue ejecutandose, lo mandamos a background
 * escribir en la consola "fg" para que vuelva
 *
 * estan los comandos fg y bg, a revisar!
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h> // sleep

// (1)
#include <signal.h>

// (4)
void handler_sigtstp(int signal_number);

void handler_sigcont(int signal_number);

int main()
{

    int x;

    // (2)
    struct sigaction sa;

    // (3)
    // configuro la estructura
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handler_sigtstp; // puntero a funcion
    sa.sa_flags = SA_RESTART;         // no funciona bien señales con scanf???!!!
    // sigaction(SIGTSTP, &sa, NULL);

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handler_sigcont; // puntero a funcion
    sa.sa_flags = SA_RESTART;         // no funciona bien señales con scanf???!!!
    sigaction(SIGCONT, &sa, NULL);

    while (1)
    {
        sleep(1);
    }

    printf("main() end\n");
    // scanf("%d", &x);
    // printf("Resultado: %d * 5 = %d\n", x, x * 5);

    return 0;
}

void handler_sigtstp(int signal_number)
{
    printf("handler_sigtstp()::stop not allow\n");
}

void handler_sigcont(int signal_number)
{
    printf("handler_sigcont(), de vuelta!\n");
    fflush(stdout);
}