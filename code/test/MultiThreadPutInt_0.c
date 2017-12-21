#include "syscall.h"

#define NB 5

/*
 * Création de plusieurs threads exécutant putInt.
 * On vérifie le bon fonctionnement des structures de synchronisation par
 * l'utilisation concurrente de synchconsole
 */

void g(void *arg) {
  PutInt(*(int *)arg);
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
