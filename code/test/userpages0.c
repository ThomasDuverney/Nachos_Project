#include "syscall.h"

void characterInterleaved(void *arg) {
  PutChar('T');
  PutChar(*(char *) arg);
  UserThreadExit();
}

void characterInterleaved1(void *arg) {
  PutChar('R');
  PutChar(*(char *) arg);
  UserThreadExit();
}


int main(){
  char c1 = 'c';
  char c2 = 'z';
  UserThreadCreate(characterInterleaved, (void *) &c1);
  UserThreadCreate(characterInterleaved1, (void *) &c2);

  return 0;
}
