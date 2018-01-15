#include "syscall.h"

int main(){
	PutString("Début Main\n");
	ForkExec("MultiThreadPutChar_Mutex_0");
	ForkExec("MultiThreadPutChar_Mutex_0");
	PutString("Fin Main\n");
	Exit(0);
}
