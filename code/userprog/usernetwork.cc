#include "usernetwork.h"
#include <string>

#ifdef NETWORK
extern void do_UserSendMessage(){
  int addrDesti = machine->ReadRegister(4);
  int boxTo = machine->ReadRegister(5);
  int boxFrom = machine->ReadRegister(6);
  int ptrData = machine->ReadRegister(7);
  char * data = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  copyStringFromMachine(ptrData,data, MAX_STRING_SIZE);
  postOffice->SendMessage(addrDesti,boxTo,boxFrom,data);
  free(data);
}

extern void do_UserReceiveMessage(){
  int ptrData = machine->ReadRegister(4);
  int box = machine->ReadRegister(5);
  //char * buffer =  (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  std::string message = postOffice->ReceiveMessage(box);
  int i = 0;
  while(i < MAX_STRING_SIZE){
    if(!machine->WriteMem(ptrData++, 1, message[i++])){
      DEBUG('f', "Error translation virtual address 0x%x.\n", ptrData-1);
    }
  }
}
#else
extern void do_UserSendMessage(){

}

extern void do_UserReceiveMessage(){

}
#endif
