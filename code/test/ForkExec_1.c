#include "syscall.h"

int main(){
	PutChar('A');
	ForkExec("PutChar_0");
	PutChar('B');
	Exit(0);
}
