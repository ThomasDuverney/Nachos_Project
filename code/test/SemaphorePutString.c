#include "syscall.h"

#define NB 5

/*
 * Création de plusieurs threads exécutant PutString.
 * On vérifie le bon fonctionnement des structures de synchronisation par
 * l'utilisation concurrente de synchconsole
 */

Sem_t sem;

void g(void *arg) {
  SemWait(sem);
  PutString("Je suis un thread ");
  PutChar('c'+*(int*) arg);
  PutChar('c'+*(int*) arg);
  PutChar('c'+*(int*) arg);
  PutChar('c'+*(int*) arg);
  PutString("\n");
  SemPost(sem);
  UserThreadExit();
}

int main(){
  int tab[NB];
  int i;
  int tid[NB];
  sem = SemCreate(1);

  for(i=0; i<NB; i++){
    tab[i] = i;
    tid[i] = UserThreadCreate(g,(void*) (tab+i));
  }

  for(i=0; i<NB; i++){
    UserThreadJoin(tid[i]);
  }
  SemDestroy(sem);
  return 0;
}
