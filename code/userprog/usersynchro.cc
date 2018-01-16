#include "usersynchro.h"
#include "system.h"

////////////////////////////////////////////////////////
//           Gestion des mutex utilisateur            //
//                                                    //
////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////
//           Gestion des  Sémaphores utilisateur      //
//                                                    //
////////////////////////////////////////////////////////

extern void do_UserSemCreate(){
  int semId = ++semCounter;
  int initialValue = machine->ReadRegister(4);
  Semaphore * semaphore = new Semaphore("Semaphore_created_by_user",initialValue);
  semMap->insert(std::make_pair(semId,semaphore));
  machine->WriteRegister(2,semId);
}

extern void do_UserSemWait(){
  int semId = machine->ReadRegister(4);
  Semaphore * semaphore = (semMap->find(semId))->second;
  semaphore->P();
}

extern void do_UserSemPost(){
  int semId = machine->ReadRegister(4);
  Semaphore * semaphore = (semMap->find(semId))->second;
  semaphore->V();
}

extern void do_UserSemDestroy(){
  int semId = machine->ReadRegister(4);
  semMap->erase(semId);
}

////////////////////////////////////////////////////////
//           Gestion des conditions mutex             //
//                utilisateur                         //
////////////////////////////////////////////////////////

extern void do_UserCondCreate(){
  int condId = ++condCounter;
  Condition * condition = new Condition("Condition_created_by_user");
  condMap->insert(std::make_pair(condId,condition));
  machine->WriteRegister(2,condId);
}

extern void do_UserCondWait(){
  int condId = machine->ReadRegister(4);
  int mutexId = machine->ReadRegister(5);
  Lock * conditionLock = (mutexMap->find(mutexId))->second;
  Condition * condition = (condMap->find(condId))->second;
  condition->Wait(conditionLock);
}

extern void do_UserCondSignal(){
  int condId = machine->ReadRegister(4);
  Condition * condition = (condMap->find(condId))->second;
  condition->Signal();
}

extern void do_UserCondBroadCast(){
  int condId = machine->ReadRegister(4);
  Condition * condition = (condMap->find(condId))->second;
  condition->Broadcast();
}

extern void do_UserCondDestroy(){
  int condId = machine->ReadRegister(4);
  condMap->erase(condId);
}
