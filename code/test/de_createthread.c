#include "syscall.h"

#define NB 15

/*
 * Création de plusieurs threads exécutant PutString.
 * Chacun des threads réalise une boucle de pour effectuer plusieurs PutString
 */

void g(void *arg) {
    PutString("Je suis un thread ");
    PutInt( *((int *) arg) );
    PutString("\n");
}


int main(){
  int tab[NB];
  int i;
  int tid[NB];
 

  for(i=0; i<NB; i++){
    tab[i] = i;
    tid[i] = UserThreadCreate(g,(void*) (tab+i));
  }

  for(i=0; i<NB; i++){
    UserThreadJoin(tid[i]);
  }
  PutString("Je suis le main j'attends les autres threads\n");

  return 0;
}
