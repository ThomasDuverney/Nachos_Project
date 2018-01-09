#include "copyright.h"
#include "process.h"

extern int processCounter;

Process::Process(const char *processName) {
  pid = ++processCounter;
  ppid = currentThread->getPid();
  processName = processName;
  nbThreadProcess = 1;

  Thread launcherThread = new Thread(processName);
  launcherThread->setPid(pid);

  threadList = new List();
  threadList.insert(launcherThread);

}

void Process::startProcess(const char * fileName){

  OpenFile *executable = fileSystem->Open (fileName);
  AddrSpace *space;

  if (executable == NULL){
    printf ("Unable to open file %s\n", fileName);
    ASSERT(FALSE);
  }

  space = new AddrSpace (executable);
  launcherThread->space = space;

  delete executable;		// close file

  space->InitRegisters ();	// set the initial register values
  space->RestoreState ();	// load page table register

  IntStatus oldLevel = interrupt->SetLevel (IntOff);
  scheduler->ReadyToRun(launcherThread);	// ReadyToRun assumes that interrupts
  // are disabled!
  (void) interrupt->SetLevel (oldLevel);

}

int Process::getPid() {
  return pid;
}

int Process::getPpid() {
  return ppid;
}

List * Process::getThreadList() {
  return threadList;
}
