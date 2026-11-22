A#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int num1 = 7;
    int num2 = 5;
    int ris;
    int status;

    pid_t pid_somma, pid_molt, pid_term;

    /* ---- Creazione del primo figlio (SOMMA) ---- */
    pid_somma = fork();
    if (pid_somma < 0) {
        perror("Errore nella fork (somma)");
        exit(1);
    }
    if (pid_somma == 0) {
        ris = num1 + num2;
        exit(ris);
    }

    /* ---- Creazione del secondo figlio (MOLTIPLICAZIONE) ---- */
    pid_molt = fork();
    if (pid_molt < 0) {
        perror("Errore nella fork (moltiplicazione)");
        exit(1);
    }
    if (pid_molt == 0) {
        ris = num1 * num2;
        exit(ris);
    }

    /* ---- PROCESSO PADRE ---- */
    /* Due wait: una per ciascun figlio */
    for (int i = 0; i < 2; i++) {
        pid_term = wait(&status);

        if (pid_term < 0) {
            perror("Errore nella wait");
            exit(1);
        }

        if (WIFEXITED(status)) {
            ris = WEXITSTATUS(status);

            if (pid_term == pid_somma)
                printf("Figlio SOMMA (pid %d): %d + %d = %d\n",
                       pid_term, num1, num2, ris);
            else if (pid_term == pid_molt)
                printf("Figlio MOLTIPLICAZIONE (pid %d): %d * %d = %d\n",
                       pid_term, num1, num2, ris);
        } else {
            printf("Il figlio %d non è terminato normalmente\n", pid_term);
        }
    }

    return 0;
}
