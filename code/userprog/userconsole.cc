#include "userconsole.h"


void do_UserPutChar(){
  int firstParam = machine->ReadRegister(4);
  synchconsole->SynchPutChar((char) firstParam);
}

void do_UserPutString(){
  int firstParam = machine->ReadRegister(4);
  char * string = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  copyStringFromMachine(firstParam, string, MAX_STRING_SIZE);
  synchconsole->SynchPutString(string);
}

void do_UserPutInt(){
  int firstParam = machine->ReadRegister(4);
  synchconsole->SynchPutInt(firstParam);
}

void do_UserGetChar(){
  char c = synchconsole->SynchGetChar();
  machine->WriteRegister(2, (int)c);
}

void do_UserGetString(){
  // reg4 = adresse du tableau de la string (memoire virtuelle)
  int ptrAdressChar= machine->ReadRegister(4);
  // reg5 = taille max
  int tailleMaxChaine = machine->ReadRegister(5);
  char * buff = (char*) malloc(tailleMaxChaine * sizeof(char));
  synchconsole->SynchGetString(buff, tailleMaxChaine);
  int h = 0;
  while(h < tailleMaxChaine){
    if(!machine->WriteMem(ptrAdressChar++, 1, buff[h++])){
      DEBUG('f', "Error translation virtual address 0x%x.\n", ptrAdressChar-1);
    }
  }
  free(buff);
}

void do_UserGetInt(){
  int ptrValRetour = machine->ReadRegister(4);
  int val;
  synchconsole->SynchGetInt(&val);
  machine->WriteMem(ptrValRetour, 4, val);
}
