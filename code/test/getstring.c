#include "syscall.h"

int main(){

	char s[20];

	// bloquant
	GetString(s, 20);


	PutString(s);
	PutString("\n");

	return 0;
}