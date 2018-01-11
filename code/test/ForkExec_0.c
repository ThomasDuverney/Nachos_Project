#include "syscall.h"

int main(){
	PutString("Debut ForkExec\n");
	ForkExec("PutString_0");
	PutString("\nFin ForkExec\n");
	PutString("\nFin ForkExec\n");
	PutString("\nFin ForkExec\n");
	PutString("\nFin ForkExec\n");
	PutString("\nFin ForkExec\n");
	PutString("\nFin ForkExec\n");
	PutString("\nFin ForkExec\n");
	return 0;
}
