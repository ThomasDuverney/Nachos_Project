#include "syscall.h"

void characterInterleaved1(void *arg) {
  int i;
  for(i=0; i<5; i++){
    PutString("Thread 1: ");
    PutInt(i);
    PutChar('\n');
  }
  UserThreadExit();
}

void characterInterleaved2(void *arg) {
  int i;
  for(i=0; i<5; i++){
    PutString("Thread 2: ");
    PutInt(i);
    PutChar('\n');
  }
  UserThreadExit();
}


int main(){
  char c1 = 'c';
  char c2 = 'z';
  UserThreadCreate(characterInterleaved1, (void *) &c1);
  UserThreadCreate(characterInterleaved2, (void *) &c2);

  return 0;
}
