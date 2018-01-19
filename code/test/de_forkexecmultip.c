#include "syscall.h"

int calculSomme(){
  int i =0;
  int somme = 0;
  for(;i<10;i++){
    somme += i;
  }
  return somme;
}
int main(){
  PutString("Debut du processus de_forkexecmultip \n");
  ForkExec("ForkExec_1");
  PutString("Fin du processus de_forkexecmultip \n");
  Exit(0);
}
