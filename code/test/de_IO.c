#include "syscall.h"

int main(){
  int i;
  char c;
  char chaine[30];
  PutString("Rentrer une chaine\n");
  GetString(chaine,30);
  PutString("La chaine saisie est : ");
  PutString(chaine);
  PutString("\n");
  PutString("Rentrer un entier\n");
  GetInt(&i);
  PutString("L'entier saisi est : ");
  PutInt(i);
  PutString("\n");
  PutString("Rentrer un caractère \n");
  c = GetChar();
  PutString("Le caractère saisi est : ");
  PutChar(c);
  PutString("\n");
  return 0;
}
