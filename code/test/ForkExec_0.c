#include "syscall.h"

int main(){
	PutChar('1');
	ForkExec("Forkexec_call");

	return 0;
}