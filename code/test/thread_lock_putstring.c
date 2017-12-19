#include "syscall.h"

#define NB 10


void g(void *arg) {
	PutString("Je suis le thread num ");
	PutInt(*(int*)arg);
	PutChar('\n');
	UserThreadExit();
}


int main(){

	int tab[NB];

	// int arg = 5;

	for(int i=0; i<NB; i++){
		tab[i] = i;
		UserThreadCreate(g, &tab[i]);
	}

	


	PutString("Je suis le thread main\n");
	PutString("Je suis le thread main\n");
	PutString("Je suis le thread main\n");
	PutString("Je suis le thread main\n");
	PutString("Je suis le thread main\n");
	PutString("Je suis le thread main\n");
	PutString("Je suis le thread main\n");
	PutString("Je suis le thread main\n");
	PutString("Je suis le thread main\n");




	return 0;
}