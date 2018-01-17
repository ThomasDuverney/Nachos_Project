#include "syscall.h"

#define NB 5

/*
 * Création de plusieurs threads exécutant putInt.
 * On vérifie le bon fonctionnement de UserThreadjoin
 * Deux join du main sur chaque thread crée.
 */

void g(void *arg) {
  PutInt(*(int *)arg);
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
    UserThreadJoin(tid[i]);
  }
  PutInt(127);
  return 0;
}
