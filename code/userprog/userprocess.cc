#include "userprocess.h"
#include "thread.h"
#include "system.h"

static void startUserProcess(int threadParams){

  currentThread->space->InitRegisters();
  currentThread->space->RestoreState();
  machine->Run();

}

extern int do_UserProcessCreate(char *filename){

  OpenFile *executable = fileSystem->Open (filename);

  if (executable == NULL){
    printf ("Unable to open file %s\n", filename);
    return -1;
  }

  Thread * threadLauncher;
  if ((threadLauncher = new Thread (filename)) == NULL) {
    return -1;
  }

  threadLauncher->space = new AddrSpace (executable);
  threadLauncher->Fork(startUserProcess,-1);

  delete executable;		// close file

  return 1;
}
