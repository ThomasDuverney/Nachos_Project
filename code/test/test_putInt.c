#include "syscall.h"


// test PutInt avec passage de variables dans une fonction
void printInt(int test){
	int i = 27;
	PutInt(i);
	PutChar('\n');
	PutInt(test);
	PutChar('\n');
}


int main(){

	int i = 35;

	PutInt(10);
	PutChar('\n');

	PutInt(202000);
	PutChar('\n');

	PutInt(i);
	PutChar('\n');

	printInt(200);

	printInt(i);

	return 0;
}