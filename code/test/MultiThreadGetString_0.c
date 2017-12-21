#include "syscall.h"

#define NB 5

/*
 * Programme de test créant plusieurs threads executant getString puis PutString.
 * On vérifie le bon fonctionnement des structures de synchronisation par
 * l'utilisation concurente de synchconsole
 */

void g(void *arg) {
  char s[10];
  GetString(s,10);
  PutString(s);
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
