#include "syscall.h"

#define NB 15

/*
 * Création de plusieurs threads exécutant PutString.
 * On vérifie le bon fonctionnement des structures de synchronisation par
 * l'utilisation concurrente de synchconsole
 */

void g(void *arg) {
  PutString("Je suis un thread\n");
  UserThreadExit();
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

  return 0;
}
