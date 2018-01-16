#include "syscall.h"
#define NB 5

void g(void *arg) {
	PutInt(*(int *)arg);
	UserThreadExit();
}

int main(){
	int tab[NB];
	int i;
	int tid[NB];

	PutString("MainDebut");
	ForkExec("ForkExec_3");

	for(i=0; i<NB; i++){
		tab[i] = i;
		tid[i] = UserThreadCreate(g,(void*) (tab+i));
	}

	for(i=0; i<NB; i++){
		UserThreadJoin(tid[i]);
	}
	PutString("MainFin");
	return(0);
}
