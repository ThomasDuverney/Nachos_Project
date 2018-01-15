#include "syscall.h"

#define NB 5

/*
 * Création de plusieurs threads exécutant putInt.
 * On vérifie le bon fonctionnement des structures de synchronisation par
 * l'utilisation concurrente de synchconsole
 */

Mutex_t mutex;

void g(void *arg) {
  int i = 0;
  MutexLock(mutex);
  for(i = 0; i<NB; i++){
    PutInt(*(int *)arg);
  }
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
