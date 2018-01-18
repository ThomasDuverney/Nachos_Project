#include "syscall.h"

int calculSomme(){
	int i =0;
	int somme = 0;
	for(;i<10;i++){
		somme += i;
	}
	return somme;
}
int main(){
	PutString("Début du programme\n");
	ForkExec("Factoriel");
	PutString("\n");
	PutInt( calculSomme() );
	Exit(0);
}
