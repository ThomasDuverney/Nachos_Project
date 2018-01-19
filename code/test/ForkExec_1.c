#include "syscall.h"

int main(){
	PutString(" * Le processus ForkExec_1 lancé par de_forkexecmulti démarre*\n");
	ForkExec("PutString_0");
	PutString(" *Le processus ForkExec_1 lancé par de_forkexecmulti termine*\n");
	Exit(0);
}
