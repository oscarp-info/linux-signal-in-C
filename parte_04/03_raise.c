// gcc -Wall raise.c -o raise

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int signal_number)
{
    printf("SIGUSR1 recived!\n");
}

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handler;
    if (sigaction(SIGUSR1, &sa, NULL) != 0)
    {
        perror("signal()");
    }
    while (1)
    {
        sleep(1);
        raise(SIGUSR1);
        // sleep(1);
        // kill(getpid(), SIGUSR1); // equivalente a raise(SIGUSR1)
    }

    return 0;
}
