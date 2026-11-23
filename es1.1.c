#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIGINT 3

static volatile sig_atomic_t contatore = 0;

/* Handler: usa solo funzioni async-signal-safe (write, non printf) */
static void gestore_sigint(int sig)
{
    (void)sig;
    contatore++;
    const char msg[] = "Hai premuto CTRL-C!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = gestore_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("In esecuzione (PID %d). Premi CTRL-C %d volte per uscire.\n",
           getpid(), MAX_SIGINT);
    fflush(stdout); /* evita di mescolare printf bufferizzato e write() */

    while (contatore < MAX_SIGINT)
        pause(); /* attende l'arrivo di un segnale */

    printf("Arrivederci!\n");
    return 0;
}
