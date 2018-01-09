// system.h
//      All global variables used in Nachos are defined here.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef SYSTEM_H
#define SYSTEM_H

#include "copyright.h"
#include "utility.h"
#include "thread.h"
#include "scheduler.h"
#include "interrupt.h"
#include "stats.h"
#include "timer.h"
#include <map>

// Initialization and cleanup routines
extern void Initialize (int argc, char **argv);	// Initialization,
						// called before anything else
extern void Cleanup ();		// Cleanup, called when
						// Nachos is done.

extern Thread *currentThread;	// the thread holding the CPU
extern Thread *threadToBeDestroyed;	// the thread that just finished
extern Scheduler *scheduler;	// the ready list
extern Interrupt *interrupt;	// interrupt status
extern Statistics *stats;	// performance metrics
extern Timer *timer;		// the hardware alarm clock

#ifdef USER_PROGRAM
#define MAX_STRING_SIZE 100
#include "machine.h"
#include "process.h"
#include "synchconsole.h"
#include "frameprovider.h"
//extern std::map<int,Process*> *processList;
extern Process *currentProcess;
extern Machine *machine;	// user program memory and registers
/*
  semExitprocess:
  Structure de synchronisation pour la fermeture d'un processus (cas momno-processus),
  On veut qu'un processus attende que tous ses threads aient fini avant de terminer.
  La sémaphore est initialisée à 0. Quand un thread est crée, on décrémente la sémaphore.
  Quand un thread se termine on incrémente la sémaphore.
  Le processus père attends que la sémaphore soit positive ou nulle (tous les threads on terminé)
  avant de quitter.
 */
extern Semaphore *semExitProcess;
/* /!\ Remarque: la variable globale nbThreadProcess n'est accédée et modifiée que par le noyau,
   qui pour l'instant est considéré comme mono-thread.
   Dans ces conditions l'accès à cette variable n'a pas besoin d'être protégé par un
   verrou.
 */

extern FrameProvider *frameProvider;

extern int nbThreadProcess; // Nombre de threads actifs du processus courant.
extern int threadCounter;

extern SynchConsole *synchconsole;
#endif // USER_PROGRAM

#ifdef FILESYS_NEEDED		// FILESYS or FILESYS_STUB
#include "filesys.h"
extern FileSystem *fileSystem;
#endif

#ifdef FILESYS
#include "synchdisk.h"
extern SynchDisk *synchDisk;
#endif

#ifdef NETWORK
#include "post.h"
extern PostOffice *postOffice;
#endif

#endif // SYSTEM_H
