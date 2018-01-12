#include "syscall.h"

int main(){
  PutChar('2');
  ForkExec("PutChar_0");
  return(0);
}
