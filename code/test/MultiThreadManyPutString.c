#include "syscall.h"

#define NB 5

/*
 * Création de plusieurs threads exécutant PutString.
 * Chacun des threads réalise une boucle de pour effectuer plusieurs PutString
 */

void g(void *arg) {
  int j;
  for(j = 0; j < 30 ; j++){
    PutString("Je suis un thread");
  }
  UserThreadExit();
}


int main(){
  int tab[NB];
  int i;

  for(i=0; i<NB; i++){
    tab[i] = i;
    UserThreadCreate(g,(void*) (tab+i));
  }

  return 0;
}
