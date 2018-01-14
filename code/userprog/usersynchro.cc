#include "usersynchro.h"
#include "system.h"

extern void do_UserMutexCreate(){
  int mutexId = ++mutexCounter;
  Lock * newLock = new Lock("Mutex_created_by_user");
  mutexMap->insert(std::make_pair(mutexId,newLock));
  machine->WriteRegister(2,mutexId);
}

extern void do_UserMutexLock(){
  int mutexId = machine->ReadRegister(4);
  Lock * lock = (mutexMap->find(mutexId))->second;
  lock->Acquire();
}

extern void do_UserMutexUnlock(){
  int mutexId = machine->ReadRegister(4);
  Lock * lock = (mutexMap->find(mutexId))->second;
  lock->Release();
}

extern void do_UserMutexDestroy(){
  int mutexId = machine->ReadRegister(4);
  mutexMap->erase(mutexId);
}
