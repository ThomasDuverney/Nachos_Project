#include "syscall.h"

int main(){
  PutString("Nouveau process\n");
  ForkExec("PutString_0");
  return(0);
}
