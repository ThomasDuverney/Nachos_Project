#include "userthread.h"
#include "thread.h"
#include "system.h"

/*
 * Lance un thread utilisateur qui execute la fonction UserThreadParams->f et prennant comme
 * arguments UserThreadparams->arg.
 */
static void StartUserThread(int threadParams){
  UserThreadParams *userThreadParams = (UserThreadParams*) threadParams;

  // Sauvegarde de l'ancienne valeur de PC pour le retour de la fonction.
  machine->WriteRegister (PrevPCReg, machine->ReadRegister (PCReg));
  //Place dans PC la prochaine instruction à éxecuter -> f
  machine->WriteRegister (PCReg, userThreadParams->f);
  // Place dans NextPcreg l'instruction suivante
  machine->WriteRegister (NextPCReg, userThreadParams->f+4);
  // Place les paramètres de la fonction dans le registre 4.
  machine->WriteRegister (4, userThreadParams->arg);
  // Libère l'espace mémoire allouée à la structure threadparams.
  free(userThreadParams);
  // Lance l'interpreteur mips -> banchement vers f.
  machine->Run();
}

/*
 * Crée un thread noyau (propulseur) qui permet le lancement d'un thread utilisateur exécutant la fonction
 * dont l'adresse est f et dont les paramètres sont fournis à l'adresse arg.
 * la fonction f et les paramètres arg sont passés à l'appel Fork à par le biais d'une structure
 * de donnée de type UserThreadParams.
 */
extern  int do_UserThreadCreate(int f, int arg){
  Thread *t;
  if ((t = new Thread ("kernel UserThread launcher")) == NULL) {return -1;}
  UserThreadParams *threadParams = (UserThreadParams*) malloc(sizeof(UserThreadParams));
  threadParams->f = f;
  threadParams->arg = arg;

  t->Fork(StartUserThread,(int) threadParams);
  currentThread->Yield();

  return (int) t;
}

extern void do_UserThreadExit(){
  currentThread->Finish();
}
