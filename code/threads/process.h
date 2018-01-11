#ifndef PROCESS_H
#define PROCESS_H

#include "copyright.h"
#include "utility.h"
#include "machine.h"
#include "thread.h"
#include <map>
/*
  Classe pour l'abstraction d'un processus utilisateur.
  Un processus possède un nom, un identificateur unique pid, l'identificateur de son père. De plus un processus maintient une map permettant de
  d'accéder aux références des différents fils d'execution par leur tid.
 */
class Process {
    public:
        Process(const char *pName);	// Initialise un process
        ~Process();		// Détruit un process

        /*
          startProcess
          Spécifications: void startProcess(char * fileName)
          Sémantique: Lance un processus utilisateur.
          Ouvre le fichier éxécutable, crée et initialise un espace d'adressage
          pour le processus. Place l'executable en mémoire,
          crée un thread propulseur noyau pour le processus et le place
          dans la readyList du scheduler.
        */
        void startProcess(char * fileName);

        /*
          finish
          Spécifications: void finish()
          Sémantique: Termine l'execution d' un processus utilisateur.
          Termine, par la méthode finnish, le thread courant
          si il appartient au processus à terminer,
          change l'état de tous les threads du processus à TERMINATED.
          Supprime les Threads TERMINATED de la readylist du scheduler
          (voir si cette opération ne peut/doit pas être faite dans
          findnexttorun())
        */
        void finish();
        int getPid();// Retourne l'identificateur du processus

        /*
          getPpid
          Spécifications: int getPpid()
          Sémantique: Retourne l'identificateur du père du processus
          Pour le processus initial pid = Ppid.
        */
        int getPpid();

        /*
          getLauncherThread
          Spécifications: Thread* getLauncherThread()
          Sémantique: Retourne la référence du thread propulseur
          du processus.
        */
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
