#include "syscall.h"

int main(){
	PutString("Debut ForkExec\n");
	ForkExec("Forkexec_call");
	PutString("\nFin ForkExec\n");
	return 0;
}
