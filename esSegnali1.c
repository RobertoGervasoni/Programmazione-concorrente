#include <stdio.h>    // printf
#include <stdlib.h>   // exit
#include <unistd.h>   // sleep 

int main()
{
  printf("\n[INIZIO]");

  //Ciclo infinito
  for(;;)
  {
    printf("\nCiclo infinito ...");
    sleep(1);
  }

  // Codice mai eseguito
  printf("\n\n[FINE]");
  exit(0);
}
