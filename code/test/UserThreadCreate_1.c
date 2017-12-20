#include "syscall.h"

#define NB 10

/*
 * Creation de plusieurs threads utilisateur qui affichent des caractères.
 * Le thread 1 doit afficher 'X' et le caractère 'a' passé en paramètre de UserThreadCreate.
 * Le thread 2 doit afficher 'Y' et 'b' passé en paramètre de UserThreadCreate.
 * Bug:
 * Le thread 1 affiche 'X' et 'b'. 
 */
void g1(void *arg) {
	char n = *(char*) arg;
	PutChar('X');
	PutChar(n);
	PutChar('\n');
	UserThreadExit();
}

void g2(void *arg) {
	char n = *(char*) arg;
	PutChar('Y');
	PutChar(n);
	PutChar('\n');
	UserThreadExit();
}



int main(){
	char a = 'a';
	char b = 'b';
	UserThreadCreate(g1, (void*) &a);
	UserThreadCreate(g2, (void*) &b);
	return 0;
}