#include "syscall.h"

#define NB 5

/*
 * Création de plusieurs threads exécutant GetChar puis Putchar.
 * On vérifie le bon fonctionnement des structures de synchronisation par
 * l'utilisation concurrente de synchconsole
 * Remarque:
 * A l'exécution, lorsqu'un thread lit un caractère sur l'entrée standard, le
 * caractère '\n' est toujours présent dans l'entrée standard.
 * Aussi, le thread suivant exécutant GetChar() récupère et affiche '\n'.
 */

unsigned int mutex;

void g(void *arg) {
  MutexLock(mutex);
  char c;
  PutString("Je suis le thread: ");
  PutInt(*(int*) arg);
  PutChar('\n');
  PutString("entrer un caractère\n");
  c = GetChar();
  PutChar(c);
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
