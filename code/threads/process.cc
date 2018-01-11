#include "process.h"
#include "system.h"

Process::Process(const char *pName) {
    pid = ++processCounter;
    if(currentThread == NULL) {
        ppid = pid; /* Le processus courant est le processus init */
    } else {
        ppid = currentThread->getPid();
    }
    processName = pName;
    launcherThread = new Thread(processName);
    launcherThread->setPid(pid);
    threadList = new std::map<int, Thread*>();
    threadList->insert(std::pair<int, Thread*>(launcherThread->getThreadID(), launcherThread));
}

Process::~Process(){
    delete threadList;
}

void Process::startProcess(char * fileName){
    OpenFile *executable = fileSystem->Open(fileName);
    AddrSpace *space;

    if (executable == NULL){
        printf ("Unable to open file %s\n", fileName);
        ASSERT(FALSE);
    }
    space = new AddrSpace (executable);
    launcherThread->space = space;
    delete executable;      // close file
    space->InitRegisters ();    // set the initial register values
    space->RestoreState (); // load page table register
    // ReadyToRun assumes that interrupts
    // are disabled!
    IntStatus oldLevel = interrupt->SetLevel (IntOff);
    if(launcherThread->getStatus() != RUNNING) {
        /* Si le thread propulseur est le thread courrant on ne l'ajoute
           pas à la ready list.
           Cette situation se produit lors de la création du premier
           processus utilisateur dans system.cc.
           Suite à la création du processus on branche le scheduler
           "à la main" sur le thread propulseur.
        */
        scheduler->ReadyToRun(launcherThread);
    }
    (void) interrupt->SetLevel (oldLevel);
}

void Process::finish(){
    for(std::map<int,Thread*>::iterator it=threadList->begin() ; it!=threadList->end() ; ++it){
        /* on détruit tous les thread de la liste sauf le thread courant qui doit être détruit par la methode finish (on travaille encore dans la pile d'éxécution de ce processus) -> threadTobedestroyed */
        if (it->second == currentThread){
            it->second->Finish(); /* it->second pour accèder à la valeur */
        } else {
            it->second->setStatus(TERMINATED);
        }
    }
    /* Suppression des threads TERMINATED de la ready list du scheduler */
    // Pas utilisé
    //IntStatus oldLevel = interrupt->SetLevel (IntOff);
    //scheduler->RemoveThreadFromReadyList();
    //(void) interrupt->SetLevel (oldLevel);
    /* TODO mettre à jour la bitmap */
}

void Process::addThread(Thread * newThread){
    threadList->insert(std::pair<int, Thread*>(newThread->getThreadID(), newThread));
    newThread->setPid(pid);
}

void Process::RemoveThread(int tid){
    threadList->erase(tid);
}

int Process::getPid() {
    return pid;
}

int Process::getPpid() {
    return ppid;
}

Thread* Process::getLauncherThread() {
    return launcherThread;
}

std::map<int,Thread*> *Process::getThreadList() {
  return threadList;
}

const char * Process::getProcessName(){
    return processName;
}
