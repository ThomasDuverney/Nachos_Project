#include "syscall.h"

int factorial(int n){
  if (n == 1) {
    return 1;
  } else {
    int step = factorial(n-1);
    return (n * step);
  }
}

int main() {
  int res = factorial(5);
  PutString("  *Début du processus factorielle*\n");
  PutString("  *");
  PutInt(res);
  PutString("*");
  PutChar('\n');
  PutString("  *Fin du processus factorielle*\n");
  return 0;
}
