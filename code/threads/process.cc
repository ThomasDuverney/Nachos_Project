#include "process.h"
#include "copyright.h"
#include "system.h"
#include "filesys.h"

extern int processCounter;

Process::Process(const char *procName) {
  pid = ++processCounter;
  ppid = currentThread->getPid();
  this->processName = procName;
  nbThreadProcess = 1;

  Thread * launcherThread = new Thread(processName);
  launcherThread->setPid(pid);

  threadList = new std::map<int,Thread *>();
  threadList->insert(std::pair<int,Thread*>(launcherThread->getThreadID(),launcherThread));

}


Process::~Process(){
  /*for (std::map<int,Thread*>::iterator it=threadList.begin(); it!=threadList.end(); ++it){

    }*/
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

std::map<int,Thread *>* Process::getThreadList() {
  return threadList;
}
