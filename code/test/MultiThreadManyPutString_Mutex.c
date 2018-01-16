#include "syscall.h"

#define NB 5

/*
 * Création de plusieurs threads exécutant PutString.
 * Chacun des threads réalise une boucle de pour effectuer plusieurs PutString
 */

unsigned int mutex;

void g(void *arg) {
  MutexLock(mutex);
  int j;
  for(j = 0; j < 10 ; j++){
    PutString("Je suis un thread \n");
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
