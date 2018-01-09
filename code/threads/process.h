#ifndef PROCESS_H
#define PROCESS_H

#include "copyright.h"
#include "utility.h"
#include "machine.h"
#include "thread.h"
#include <map>

class Process{

 public:
  const char *processName;
  int pid;
  int ppid;
  std::map<int,Thread *> * threadList;
  int nbThreadProcess;


  Process(const char * procName);	// Initialise un process
  ~Process ();		// Détruit un process

  int getPid();
  int getPpid();

  std::map<int,Thread *>* getThreadList();
  void startProcess(const char * fileName);

};

#endif				// PROCESS_H
