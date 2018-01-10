#ifndef PROCESS_H
#define PROCESS_H

#include "copyright.h"
#include "utility.h"
#include "machine.h"
#include "thread.h"
#include <map>

extern int nbThreadProcess;

class Process {
    public:
        Process(const char *pName);	// Initialise un process
        ~Process();		// Détruit un process
        void startProcess(char * fileName);
        int getPid();
        int getPpid();
        void finish();
        Thread* getFirstThread();
        std::map<int,Thread*> *getThreadList();
    private:
        const char *processName;
        int pid;
        int ppid;
        std::map<int,Thread*> *threadList;
        Thread* firstThread;
};

#endif				// PROCESS_H
