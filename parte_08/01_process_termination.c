/*
 * demo para generar la señal SIGINT y verificar el valor de retorno
 * presionar Ctrl-C para que se ejecute el handler por default y termine
 * verificar con el comando #echo $? el valor retornado por nuestro proceso
 * el valor 130 en decimal es 10000010 en binario
 *
 * bc <<< "obase=2;130"
 *
 *
 */
#include <stdio.h>
#include <unistd.h> // sleep
#include <stdlib.h> // EXIT_FAILURE
#include <signal.h>
#include <string.h>

void handler_sigint(int signal_number);
void printbits(int x);

int main()
{
    fprintf(stderr, "Presionar Ctrl-C, luego echo $? comparar con ...\n");
    printbits(130);
    pause();

    return 0;
}

void handler_sigint(int signal_number)
{
    fprintf(stderr, "handler_sigint:: caught signal %d\n", signal_number);
    return;
}

void printbits(int x)
{
    for (int i = sizeof(x) << 3; i; i--)
        putchar('0' + ((x >> (i - 1)) & 1));
}