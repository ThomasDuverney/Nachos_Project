#include "syscall.h"

int atoi(char * str){
  int res = 0;  // Initialisation du résultat
  int sign = 1;  // Initialisation du flag signe comme positif
  int i = 0;

  /* Si le première caractère de la chaine est "-" alors le nombre
     est négatif */
  if (str[0] == '-')
    {
      sign = -1;
      i++;
    }

  /* Itère sur chaque caractère de la chaine et met à jour le résultat */
  for (; str[i] != '\0'; ++i)
    res = res*10 + str[i] - '0';

  // Retourne le résultat avec le signe correspondant
  return sign*res;
}

int main(){
  char * str = "1";
  PutInt(atoi(str));
  return 0;
}
