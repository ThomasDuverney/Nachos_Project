#include "syscall.h"

#define NB 5

/*
 * Création de plusieurs threads exécutant getString puis PutString.
 * On vérifie le bon fonctionnement des structures de synchronisation par
 * l'utilisation concurrente de synchconsole
 */
unsigned int mutex;

void g(void *arg) {
  MutexLock(mutex);
  char s[10];
  int i;

  for (i=0; i<10; i++) {
    s[i] = 'a';
  }
  s[9] = '\n';

  GetString(s,10);
  PutString(s);
  PutChar('\n');
  MutexUnlock(mutex);
  UserThreadExit();
}


int main(){
  int tab[NB];
  int i;
  int tid[NB];
  mutex = MutexCreate();
  for(i=0; i<NB; i++){
    tab[i] = i;
    tid[i] = UserThreadCreate(g,(void*) (tab+i));
  }

  for(i=0; i<NB; i++){
    UserThreadJoin(tid[i]);
  }
  MutexDestroy(mutex);
  return 0;
}
