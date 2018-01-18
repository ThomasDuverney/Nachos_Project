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
    PutString("    **");
    PutString("Je suis le thread du processus MultiThreadPutInt_Mutex_0 :");
    PutInt(*(int *)arg);
    PutString("**\n");
  }
  MutexUnlock(mutex);
  UserThreadExit();
}


int main(){
  PutString("    **Début du processus MultiThreadPutInt_Mutex_0**\n");
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
  PutString("    **Fin du processus MultiThreadPutInt_Mutex_0**\n");
  return 0;
}
