#include "syscall.h"

int main(){

	char s[1000];

	// bloquant
	GetString(s, 1000);

	PutString("Bonjour");
	PutString(s);


	return 0;
}