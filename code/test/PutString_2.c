#include "syscall.h"
/*
  Affichage d'une chaine de taille suppérieure à la constante
  MAX_STRING_SIZE(=100) définie dans system.h.
 */
int main() {
    int t = 100;
    int depassement = 10;
    char string[t+depassement];
    int i;
    /* Remplissage du buffer */
    for(i=0; i<t; i++) {
        string[i] = '1';
    }
    for(i=0; i<depassement; i++) {
        string[t+i] = 'x';
    }

    PutString(string);
    PutString("");
    return(0);
}
