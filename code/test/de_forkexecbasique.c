#include "syscall.h"

int main(){
	PutString("Lance le programme PutInt_0");
	ForkExec("PutInt_0");
	Exit(0);
}