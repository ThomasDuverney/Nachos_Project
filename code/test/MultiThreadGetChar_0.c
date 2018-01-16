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

void g(void *arg) {
  char c;
  c = GetChar();
  PutString("Je suis le thread: ");
  PutInt(*(int*) arg);
  PutChar('\n');
  PutChar(c);
  PutChar('\n');
  UserThreadExit();
}


int main(){
  int tab[NB];
  int i;
  int tid[NB];

  for(i=0; i<NB; i++){
    tab[i] = i;
    tid[i] = UserThreadCreate(g,(void*) (tab+i));
  }

  for(i=0; i<NB; i++){
    UserThreadJoin(tid[i]);
  }

  return 0;
}
