/*
 * ejemplo para obtener informacion adicional con señales: siginfo
 */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h> // pause

void handler(int signal_number, siginfo_t *siginfo, void *context);

int main()
{

    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));

    // no utilizo sa_handler
    // sa.sa_handler = &handler;

    sa.sa_sigaction = &handler;

    // SA_NODEFER -- don't block the signal when it's handler is running
    // SA_SIGINFO -- get aditional information
    sa.sa_flags = SA_NODEFER | SA_SIGINFO;

    sigaction(SIGINT, &sa, NULL);

    while (1)
        pause();

    return 0;
}

void handler(int signal_number, siginfo_t *siginfo, void *context)
{
    // get pid of sender,
    pid_t sender_pid = siginfo->si_pid;

    printf("INT(%d), from [%d]\n", signal_number, (int)sender_pid);

    return;
}
