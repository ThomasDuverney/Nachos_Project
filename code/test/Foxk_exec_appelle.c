#include "syscall.h"

int main(){
  PutString("Nouveau process");
  ForkExec("PutString_0");
  return(0);
}
