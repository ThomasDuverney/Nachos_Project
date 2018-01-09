#include "copyright.h"
#include "process.h"
#include "system.h"

int nbThreadProcess;

Process::Process(const char *pName) {
  pid = ++processCounter;
  ppid = currentThread->getPid();
  processName = pName;
  nbThreadProcess = 1;

  Thread *launcherThread = new Thread(processName);
  launcherThread->setPid(pid);

  threadList->insert(std::pair<int, Thread*>(launcherThread->getPid(), launcherThread));
  firstThread = launcherThread;
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
