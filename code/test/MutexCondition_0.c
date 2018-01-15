#include "syscall.h"

#define NB 2

/*
 * Création de plusieurs threads exécutant PutString.
 * On vérifie le bon fonctionnement des structures de synchronisation par
 * l'utilisation concurrente de synchconsole
 */

Cond_t cond;
Mutex_t mutex;
int checkNumber;

struct threadParam{
  int * size;
};

struct threadParam p;

void g(void *arg) {
  MutexLock(mutex);
  while(checkNumber == 1){
    CondWait(cond);
  }
  checkNumber++;
  CondSignal(cond);
  MutexUnlock(mutex);
  UserThreadExit();
}

int main(){
  int tab[NB];
  int i;
  int tid[NB];

  *(p.size) = 0;
  cond = CondCreate();
  mutex = MutexCreate();
  checkNumber = 0;

  for(i=0; i<NB; i++){
    tab[i] = i;
    tid[i] = UserThreadCreate(g,(void*) (tab+i));
  }

  for(i=0; i<NB; i++){
    UserThreadJoin(tid[i]);
  }
  CondDestroy(cond);
  return 0;
}
