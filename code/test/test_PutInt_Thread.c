#include "syscall.h"


// test PutInt avec passage de variables dans une fonction
void printInt(void * test){
	int i = 27;
	PutInt(i);
	UserThreadExit();
}


int main(){

	int i = 200;

	PutInt(i);
	PutChar('\n');

	UserThreadCreate(printInt, (void *) i);

	return 0;
}