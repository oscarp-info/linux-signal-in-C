// gcc -Wall sigalmr.c -o sigalmr
// kill -l

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

void contar_segundos(int signal_number);

int main()
{
    signal(SIGALRM, contar_segundos);

    while (1)
    {
        // Establecemos una alarma para dentro de un segundo
        alarm(1);
        // Pausamos la ejecución del programa para que
        // se quede esperando a recibir una señal.
        pause();
    }
}

// Esta es la función que se va a ejecutar cada vez que se reciba la // señal SIGALRM
void contar_segundos(int signal_number)
{
    // Usamos static para que se conserve el valor de "segundos"
    // entre cada llamada a la función
    static int segundos = 0;

    segundos++;
    printf("Han pasado %d segundos.\n", segundos);
}
