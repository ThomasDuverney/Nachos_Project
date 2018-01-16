#include "syscall.h"
#define NB 5

Mutex_t mutex;

void g(void *arg) {
	int i = 0;
	MutexLock(mutex);
	for( i = 0; i<NB; i++){
		PutInt(*(int *)arg);
	}
	MutexUnlock(mutex);
	UserThreadExit();
}

int main(){
	int tab[NB];
	int i;
	int tid[NB];

	mutex = MutexCreate();

	PutString("MainDebut");
	ForkExec("ForkExec_3");

	for(i=0; i<NB; i++){
		tab[i] = i+5;
		tid[i] = UserThreadCreate(g,(void*) (tab+i));
	}

	for(i=0; i<NB; i++){
		UserThreadJoin(tid[i]);
	}
	PutString("MainFin");
	MutexDestroy(mutex);
	return(0);
}
