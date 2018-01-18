#include "syscall.h"

int main(){

  PutString("Début du processus forkexecthreads\n");
  ForkExec("MultiThreadPutInt_Mutex_0");
  PutString("Fin du processus forkexecthreads\n");
  return(0);
}
