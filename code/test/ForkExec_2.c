#include "syscall.h"

int main(){
	PutString("MainDebut");
	ForkExec("ForkExec_0");
	PutString("MainFin");
	Exit(0);
}
