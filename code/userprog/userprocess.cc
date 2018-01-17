#include "userprocess.h"
#include "system.h"

static void startUserProcess(int threadParams){

  currentThread->space->InitRegisters();
  currentThread->space->RestoreState();
  machine->Run();

}

extern int do_UserProcessCreate(){
  int ptrFileName = machine->ReadRegister(4);
  char * executableName = executableName = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  copyStringFromMachine(ptrFileName, executableName, MAX_STRING_SIZE);
  OpenFile *executable = fileSystem->Open (executableName);

  if (executable == NULL){
    printf ("Unable to open file %s\n", executableName);
    return -1;
  }

  Thread * threadLauncher;
  if ((threadLauncher = new Thread (executableName)) == NULL) {
    return -1;
  }

  threadLauncher->space = new AddrSpace (executableName);
  threadLauncher->Fork(startUserProcess,-1);

  delete executable;		// close file

  return 1;
}

/* Supprimer l'espace d'adressage du thread courant ne semble pas avisé
   il faut déléguer la tache à un autre thread comme pour la méthode finish()*/
extern void do_UserProcessFinish(Thread *t) {
  unsigned int i = 0;
  TranslationEntry * pageTable = t->space->getPageTable();
  unsigned int numPages = t->space->getNumPages();

  // libère les frames mémoire utilisées par ce processus.
  for(i= 0; i<numPages;i++){
    frameProvider->ReleaseFrame( pageTable[i].physicalPage );
  }

  //Supprime l'espace d'adressage du processus
  delete t->space;
}
