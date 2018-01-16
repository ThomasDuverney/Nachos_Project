#include "syscall.h"
#define NB 5

unsigned int mutex;

int main(){
	mutex = MutexCreate();

	PutString("MainDebut_0\n");

	ForkExec("ForkExec_Multithread_0");

	PutString("MainFin_0\n");
	MutexDestroy(mutex);
	return(0);
}
