#include "syscall.h"

/*
   Creation de plusieurs threads utilisateur qui affichent un entier.
 */
void g(void *arg) {
	int n = *(int*) arg;
	PutString("Debut fonction g");
	PutInt(n);
	PutString("\nBlabla\n");
	PutString("Blabla\n");
	PutString("Blabla\n");
	PutString("Blabla\n");

	UserThreadExit();
}


int main(){
	PutString("Debut main\n");
	int arg1 = 1;
	int arg2 = 2;
	int tid1 = UserThreadCreate(g, (void *)arg1);
	int tid2 = UserThreadCreate(g, (void *)arg2);
	PutString("Debut Join1\n");
	int ret1 = UserThreadJoin(tid1);
	PutString("Debut Join1\n");
	int ret2 = UserThreadJoin(tid2);
	PutString("Fin Join1 ret=");
	PutInt(ret1);
	PutString("\nFin Join2 ret=");
	PutInt(ret2);
	PutString("\nFin main\n");
	return 0;
}
