#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // Il processo padre inizializza le variabili
    int base = 8;
    int altezza = 5;
    int risultato;

    // Creazione del processo figlio
    pid_t pid = fork();

    if (pid < 0) {
        // Gestione dell'errore nella creazione del processo
        perror("Errore nella fork");
        return 1;
    } 
    else if (pid == 0) {
        // --- CODICE DEL PROCESSO FIGLIO ---
        // Il figlio riceve una copia separata della memoria del padre
        risultato = 2 * (base + altezza);
        printf("[FIGLIO]  Perimetro del rettangolo: %d\n", risultato);
    } 
    else {
        // --- CODICE DEL PROCESSO PADRE ---
        risultato = base * altezza;
        printf("[PADRE]   Area del rettangolo: %d\n", risultato);

        // Attesa del completamento del figlio per evitare processi zombie
        wait(NULL);
    }

    return 0;
}
