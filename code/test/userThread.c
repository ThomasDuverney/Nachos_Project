#include "syscall.h"

void print(void * c){
  PutChar('c');
  PutChar('x');
  UserThreadExit();
}

int main() {
  char c  ='c';
  UserThreadCreate(print, &c);
  PutChar('A');
  return 0;
}
