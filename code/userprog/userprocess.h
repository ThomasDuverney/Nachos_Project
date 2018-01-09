#ifndef PROCESS_H
#define PROCESS_H

#include "copyright.h"
#include "utility.h"

#ifdef USER_PROGRAM
#include "machine.h"
#include "addrspace.h"
#endif

class Process
{
  private:
      int pid;
      int ppid;
      TranslationEntry * pageTable;
      unsigned numPages;

  public:
      Process(const char * fileName);	// Initialise un process
     ~Process ();		// Détruit un process

    int getPid();
    int getPpid();

};

#endif				// PROCESS_H
