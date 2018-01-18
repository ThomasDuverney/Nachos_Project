#include "syscall.h"

#define NB 15

/*
 * Création de plusieurs threads exécutant PutString.
 * Chacun des threads réalise une boucle de pour effectuer plusieurs PutString
 */

unsigned int mutex;

void g(void *arg) {
  MutexLock(mutex);
  PutString("Je suis un thread ");
  PutInt( *((int *) arg) );
  PutString("\n");
  MutexUnlock(mutex);
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
  PutString("Je suis le main j'attends les autres threads\n");
  MutexDestroy(mutex);
  return 0;
}
