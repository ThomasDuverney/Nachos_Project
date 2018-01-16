#include "syscall.h"

#define NB 5

/*
 * Création de plusieurs threads exécutant putchar.
 */
Mutex_t mutex;

void g(void *arg) {
  MutexLock(mutex);
  PutChar('c'+*(int*) arg);
  PutChar('c'+*(int*) arg);
  PutChar('c'+*(int*) arg);
  PutChar('c'+*(int*) arg);
  MutexUnlock(mutex);
}

int main(){
  int tab[NB];
  int i;
  int tid[NB];
  mutex  = MutexCreate();
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
