#ifndef PROCESS_H
#define PROCESS_H

#include "copyright.h"
#include "utility.h"
#include "machine.h"
#include "thread.h"
#include <map>

class Process {
    public:
        Process(const char *pName);	// Initialise un process
        ~Process();		// Détruit un process
        void startProcess(char * fileName);
        int getPid();
        int getPpid();
        void finish();
        Thread* getLauncherThread();
        std::map<int,Thread*> *getThreadList();
        void addThread(Thread * newThread);
        void RemoveThread(int tid);
        const char * getProcessName();
    private:
        const char *processName;
        int pid;
        int ppid;
        std::map<int,Thread*> *threadList;
        Thread* launcherThread;
};

#endif				// PROCESS_H
