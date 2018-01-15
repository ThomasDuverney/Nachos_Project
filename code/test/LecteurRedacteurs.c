#include "syscall.h"

#define NB_ITERATIONS 1;
#define NB_LECTEURS 3;
#define NB_REDACTEURS 1;

int nbLs;
int nbLa;
int enEcriture;
int donnee = 0;
Cond_t fileL;
Cond_t fileR;
Mutex_t mutex;

void debut_redaction() {
  MutexLock(mutex);
  while(enEcriture || nbLa> 0) {
    CondWait(fileR, mutex);
  }
  enEcriture = 1;
  MutexUnlock(mutex);
  //return;
}

void debut_lecture() {
  MutexLock(mutex);
  nbLs++;
  while(enEcriture) {
    CondWait(fileL, mutex);
  }
  nbLs--;
  nbLa++;
  MutexUnlock(mutex);
  //return;
}

void fin_redaction() {
  MutexLock(mutex);
  enEcriture = 0;
  if(nbLs == 0) {
    CondSignal(fileR);
  } else {
    CondBroadCast(fileL);
  }
  MutexUnlock(mutex);
  //return;
}

void fin_lecture(){
  MutexLock(mutex);
  nbLa--;
  if(nbLa == 0){
    CondSignal(fileR);
  }
  MutexUnlock(mutex);
  //return;
}

void lecteur(void *args) {
  int i= 0;
  int valeur = 0;
  int iter = NB_ITERATIONS;
  int threadNumber = *(int *)args;
  for(i=0 ; i<iter ; i++) {
    debut_lecture();
    valeur = donnee;
    // sleep;

    MutexLock(mutex);
    PutString("Debut Lecture Thread: ");
    PutInt(threadNumber);
    PutChar('\n');
    if (valeur != donnee) {
      PutString("LECTURE INCOHERENTE !!!\n");
    }
    else {
      PutString("lecture coherente\n");
    }
    MutexUnlock(mutex);
    fin_lecture();
  }

  MutexLock(mutex);
  PutString("Thread: ");
  PutInt(threadNumber);
  PutString(" Fin lecture\n");
  MutexUnlock(mutex);
  UserThreadExit();
}

void redacteur(void *args) {
  int i, valeur;
  int iter = NB_ITERATIONS;
  int threadNumber = *(int *)args;

  for (i=0; i < iter; i++) {
    //sleep
    MutexLock(mutex);
    PutString("Debut Redaction Thread: ");
    PutInt(threadNumber);
    PutChar('\n');
    MutexUnlock(mutex);
    debut_redaction();
    valeur = threadNumber;
    donnee = valeur;
    //sleep
    MutexLock(mutex);
    PutString("Thread: ");
    PutInt(threadNumber);
    PutChar('\n');
    if (valeur != donnee)
      PutString("REDACTION INCOHERENTE !!!\n");
    else
      PutString("redaction coherente......\n");
    MutexUnlock(mutex);
    fin_redaction();
  }
  PutString("fin redaction....\n");
  UserThreadExit();
}

int main(){
  int nbL = NB_LECTEURS;
  int nbR = NB_REDACTEURS;
  int tid[nbL + nbR];
  int tab[nbL + nbR];
  int i;

  /* Initialisation des variables globales */
  mutex = MutexCreate();
  fileL = CondCreate();
  fileR = CondCreate();
  nbLs = 0;
  nbLa = 0;
  enEcriture = 0;

  for (i=0; i<nbL; i++) {
    tab[i] = i;
    tid[i] = UserThreadCreate(lecteur,(void*) (tab+i));
  }

  for (i=0; i<nbR; i++) {
    tab[nbL + 1 + i] = nbL + 1 + i;
    tid[nbL + 1 + i] = UserThreadCreate(redacteur,(void*) (tab+i));
  }

  for (i=0; i<nbL + nbR; i++) {
    UserThreadJoin(tid[i]);
  }

  MutexDestroy(mutex);
  CondDestroy(fileL);
  CondDestroy(fileR);
  return 0;
}
