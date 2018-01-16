#include "syscall.h"

/*
   Creation de plusieurs threads utilisateur qui affichent un entier.
 */
void g(void *arg) {
	PutString("Debut fonction g\n");
	PutString("Blabla\n");
	PutString("Blabla\n");
	PutString("Blabla\n");
	PutString("Blabla\n");

	UserThreadExit();
}


int main(){
	PutString("Debut main\n");
	int arg = 5;
	int tid = UserThreadCreate(g, (void *)arg);
	PutString("Debut Join\n");
	int ret = UserThreadJoin(tid);
	PutString("Fin Join\n");
	PutInt(ret);
	PutString("\nFin main\n");
	return 0;
}
