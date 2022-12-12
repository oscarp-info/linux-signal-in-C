// Ejecutar el programa y presionar Ctrl-C, verificar que el programa ahora imprime un mensaje y NO termina
// Detras de escena lo que sucede es que el kernel envia la señal INT a nuestro proceso
// y nuestro handler() atiende esta señal
// para finalizar ejecutar desde otra consola kill -KILL <pid>

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// prototipo para el handler de la señal
void handler(int signal_number);

int main()
{

    // declarar la estructura para el manejo de señales
    struct sigaction sa;

    // inicializo la estructura
    memset(&sa, 0, sizeof(sa));

    // asocio el handler (funcion)
    sa.sa_handler = &handler;

    // cambio el comportamiento de la señal en funcion a la configuracion de la estructura 'sa'
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