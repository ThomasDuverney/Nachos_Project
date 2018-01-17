#include "syscall.h"
/*
  Lecture d'une chaine de caractères de moins de 20 caractères depuis l'entrée standard.
  Affichage de la chaîne.
*/
int main(){
	char s[20];
	GetString(s, 20);
	PutString(s);
	PutString("\n");

	return 0;
}
