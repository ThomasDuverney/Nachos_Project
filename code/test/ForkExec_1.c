#include "syscall.h"

int main(){
	PutChar('1');
	ForkExec("PutChar_0");
	return 0;
}
