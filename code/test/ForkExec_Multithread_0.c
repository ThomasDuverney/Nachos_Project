#include "syscall.h"

int main(){
	PutString("DebutMain\n");
	ForkExec("MultiThreadPutInt_Mutex_0");
	PutString("FinMain\n");
	Exit(0);
}
