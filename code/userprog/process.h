#ifndef PROCESS_H
#define PROCESS_H

#include "copyright.h"
#include "utility.h"


#ifndef USER_PROGRAM
#include "machine.h"


class Process
{
 private:
  const char *processName;
  int pid;
  int ppid;
  List * threadList;
  int nbThreadProcess;
 public:

  Process(const char * fileName);	// Initialise un process
  ~Process ();		// Détruit un process

  int getPid();
  int getPpid();

  List * getThreadList();
  AddrSpace getAddrSpace();

};

#endif

#endif				// PROCESS_H
