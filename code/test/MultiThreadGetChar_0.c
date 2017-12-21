#include "syscall.h"

#define NB 5

/*
 * Programme de test créant plusieurs threads executant GetChar puis Putchar.
 * On vérifie le bon fonctionnement des structures de synchronisation par
 * l'utilisation concurente de synchconsole
 * Remarque:
 * A l'execution, lorqu'un thread lit un caractère sur l'entrée standart, le
 * caractère '\n' est toujours présent dans l'entrée standart.
 * Aussi, le thread suivant executant GetChar() récupère et affiche '\n'.
 */

void g(void *arg) {
  char c;
  c = GetChar();
  PutString("Je suis le thread: ");
  PutInt(*(int*) arg);
  PutChar('\n');
  PutChar(c);
  UserThreadExit();
}


int main(){
  int tab[NB];
  int i;

  for(i=0; i<NB; i++){
    tab[i] = i;
    UserThreadCreate(g,(void*) (tab+i));
  }

  return 0;
}
