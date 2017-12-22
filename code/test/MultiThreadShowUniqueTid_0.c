#include "syscall.h"

#define NB 5

/*
 * Programme de test créant plusieurs threads executant affichant leur TID avec un PuInt.
 * On vérifie que le système donne un identifiant unique à chacun des threads créés
 */

void g(void *arg) {
  UserThreadExit();
}


int main(){
  int tab[NB];
  int i;
  int tid;

  for(i=0; i<NB; i++){
    tab[i] = i;
    tid = UserThreadCreate(g,(void*) (tab+i));
    PutInt(tid);
    PutChar('\n');
  }

  return 0;
}
