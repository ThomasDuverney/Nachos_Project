#include "syscall.h"

int main(){
	PutInt(555);
	ForkExec("PutInt_0");
	PutInt(666);
	Exit(0);
}
