#include "syscall.h"


// test PutInt avec passage de variables dans une fonction
void printInt(int test){
	PutInt(test);
	PutChar('\n');
}


int main(){

	int i = 5;

	PutInt(10);
	PutChar('\n');

	PutInt(202000);
	PutChar('\n');

	printInt(200);

	printInt(i);

	return 0;
}