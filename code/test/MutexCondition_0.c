#include "syscall.h"

#define NB 2

/*
 *
 */

Cond_t cond;
Mutex_t mutex;
int checkNumber;

void g(void *arg) {
  MutexLock(mutex);
  while(checkNumber <= 0){
    PutInt(checkNumber);
    checkNumber++;
    CondWait(cond,mutex);
    PutInt(666);
  }
  checkNumber = checkNumber+5;
  CondSignal(cond);
  MutexUnlock(mutex);
  PutInt(89);
}

int main(){
  int tab[NB];
  int i;
  int tid[NB];

  cond = CondCreate();
  mutex = MutexCreate();
  checkNumber = 0;

  for(i=0; i<NB; i++){
    tab[i] = i;
    tid[i] = UserThreadCreate(g,(void*) (tab+i));
  }


  for(i=0; i<NB; i++){
    UserThreadJoin(tid[i]);
  }
 
  CondDestroy(cond);
  return 0;
}
