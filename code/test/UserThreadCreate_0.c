#include "syscall.h"

#define NB 10

/*
 * Creation de plusieurs threads utilisateur qui affichent un entier.
 */
void g(void *arg) {
	int n = *(int*) arg;
	//PutString("Je suis le thread num ");
	PutInt(n);
	PutChar('\n');
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
