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

////////////////////////////////////////////////////////
//           Gestion des  Sémaphores utilisateur      //
//                                                    //
////////////////////////////////////////////////////////

extern void do_UserSemInit(){
  int semId = ++semCounter;
  int initialValue = machine->ReadRegister(4);
  Semaphore * newSem = new Semaphore("Semaphore_created_by_user",initialValue);
  semMap->insert(std::make_pair(semId,newSem));
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
