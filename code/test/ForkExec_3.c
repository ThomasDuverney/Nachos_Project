#include "syscall.h"

int main(){
	PutString(" *Début du processus forkExec_3*\n");
	ForkExec("MultiThreadPutInt_Mutex_0");
	PutString(" *Fin du processus forkExec_3*\n");
	Exit(0);
}
