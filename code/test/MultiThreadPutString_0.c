#include "syscall.h"

#define NB 5

/*
 * Programme de test créant plusieurs threads executant PutString.
 * On vérifie le bon fonctionnement des structures de synchronisation par
 * l'utilisation concurente de synchconsole
 */

void g(void *arg) {
  PutString("Je suis un thread");
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
