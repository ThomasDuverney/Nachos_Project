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
	PutString("Début du processus forkExecbasique \n");
	ForkExec("Factoriel");
	PutString("\n");
	PutInt( calculSomme() );
	PutString("\n");
	PutString("Fin du processus forkExecbasique \n");
	Exit(0);
}
