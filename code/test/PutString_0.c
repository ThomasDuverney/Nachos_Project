#include "syscall.h"
/*
  Affichage d'une chaine de caractères sur la sortie standart.
 */
int main() {
    PutString("    **Le programme PutString lancé par ForkExec_1 démare**\n");
    PutString("    **ABCDEFGHIJKLMNOPQRSTUVWXYZ**\n");
    PutString("    **Le programme PutString lancé par ForkExec_1 termine**\n");
    return(0);
}
