// Ejecutar el programa y presionar Ctrl-C, verificar que el programa termina
// Detras de escena lo que sucede es que el kernel envia la señal INT a nuestro proceso

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = getpid();
    printf("pid=%d\n", pid);

    while (1)
        sleep(2);

    return 0;
}
