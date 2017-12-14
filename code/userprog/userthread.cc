#include "userthread.h"
#include "thread.h"
#include "system.h"
static void StartUserThread(int f){
    //On doit récupérer les deux arguments uniquement a l'aide de int f !
    //Placer le registre du pointeur sur la fonction f (la mettre en memoire ?) et mettre le(s) arguments (a mettre en memoire ?) dans les registres 4/5/6/7 ...
    //Puis lancer la fonction (machine->Run()) voir dans progtest StartProcess ce qui est fait je pense que c'est similaire
    machine->WriteRegister (PrevPCReg, machine->ReadRegister (PCReg));
    machine->WriteRegister (PCReg, f);
    machine->WriteRegister (NextPCReg, f+4);
    machine->WriteRegister (4, machine->ReadRegister(HiReg));
    machine->Run();
}

int do_UserThreadCreate(int f, int arg){
    Thread *t;
    if((t = new Thread ("User_Thread")) == NULL) {return -1;}
    machine->WriteRegister(HiReg, arg);
    t->Fork(StartUserThread,f);
    currentThread->Yield();
    return 0;
}

void do_UserThreadExit(){
    currentThread->space->~AddrSpace();
    currentThread->Finish();
}
