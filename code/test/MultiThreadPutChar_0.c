#include "syscall.h"

#define NB 5

/*
 * Création de plusieurs threads exécutant getString puis PutString.
 * On vérifie le bon fonctionnement des structures de synchronisation par
 * l'utilisation concurrente de synchconsole
 */

void g(void *arg) {
  PutChar('c'+*(int*) arg);
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
