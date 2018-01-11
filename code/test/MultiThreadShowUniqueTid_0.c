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
  int tid[NB];

  for(i=0; i<NB; i++){
    tab[i] = i;
    tid[i] = UserThreadCreate(g,(void*) (tab+i));
    PutInt(tid[i]);
    PutChar('\n');
  }

  for(i=0; i<NB; i++){
    UserThreadJoin(tid[i]);
  }

  return 0;
}
