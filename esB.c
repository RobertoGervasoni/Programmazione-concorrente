#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int num1 = 7;
    int num2 = 5;
    int ris;
    int operazione = 1;   /* 1 = somma, 2 = moltiplicazione */

    pid_t pid = fork();

    if (pid < 0) {
        perror("Errore nella fork");
        exit(1);
    }

    if (pid == 0) {
        /* ---- PROCESSO FIGLIO ---- */
        if (operazione == 1)
            ris = num1 + num2;
        else if (operazione == 2)
            ris = num1 * num2;
        else
            ris = 0;

        exit(ris);   /* il risultato diventa l'exit status */
    }
    else {
        /* ---- PROCESSO PADRE ---- */
        int status;

        wait(&status);

        if (WIFEXITED(status)) {
            ris = WEXITSTATUS(status);
            printf("Operazione: %s\n", (operazione == 1) ? "somma" : "moltiplicazione");
            printf("num1 = %d, num2 = %d\n", num1, num2);
            printf("Exit status del figlio (risultato) = %d\n", ris);
        } else {
            printf("Il figlio non è terminato normalmente\n");
        }
    }

    return 0;
}
