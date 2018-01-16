#include "syscall.h"
/*
  Lecture d'un entier depuis l'entrée standard.
  Ecriture de cet entier sur la sortie standard.
*/
int main(){
	int i;
	GetInt(&i);
	PutInt(i);
	return 0;
}
