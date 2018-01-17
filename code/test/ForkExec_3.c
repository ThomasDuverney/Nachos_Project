#include "syscall.h"

int main(){
	PutChar('A');
	ForkExec("MultiThreadPutInt_Mutex_0");
	PutChar('B');
	Exit(0);
}
