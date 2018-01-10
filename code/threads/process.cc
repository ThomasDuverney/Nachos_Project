#include "process.h"
#include "system.h"

int nbThreadProcess;

Process::Process(const char *pName) {
    pid = ++processCounter;

    if(currentThread == NULL) {
        ppid = pid; /* Le processus courant est le processus init */
    } else {
        ppid = currentThread->getPid();
    }
    processName = pName;
    nbThreadProcess = 1;

    Thread *launcherThread = new Thread(processName);
    launcherThread->setPid(pid);
    threadList = new std::map<int, Thread*>();
    threadList->insert(std::pair<int, Thread*>(launcherThread->getThreadID(), launcherThread));
    firstThread = launcherThread;
}

Process::~Process(){

    

    delete threadList;
}


void Process::finish(){

    /*for(threadList::iterator it=threadList.begin() ; it!=threadList.end() ; ++it){
        // on détruit tous les thread de la liste sauf le thread courant qui sera détruit par le scheduler
        if (it->second == currentThread){
            it->second->Finish(); // accede à la valeur
        } else {
            it->second->setStatus(TERMINATED);
        }
    }
*/
}

void Process::startProcess(char * fileName){

    OpenFile *executable = fileSystem->Open(fileName);
    AddrSpace *space;

    if (executable == NULL){
        printf ("Unable to open file %s\n", fileName);
        ASSERT(FALSE);
    }

    space = new AddrSpace (executable);
    firstThread->space = space;

    delete executable;		// close file

    space->InitRegisters ();	// set the initial register values
    space->RestoreState ();	// load page table register

    IntStatus oldLevel = interrupt->SetLevel (IntOff);
    scheduler->ReadyToRun(firstThread);	// ReadyToRun assumes that interrupts
    // are disabled!
    (void) interrupt->SetLevel (oldLevel);

}

int Process::getPid() {
    return pid;
}

int Process::getPpid() {
    return ppid;
}

Thread* Process::getFirstThread() {
    return firstThread;
}

std::map<int,Thread*> *Process::getThreadList() {
  return threadList;
}
