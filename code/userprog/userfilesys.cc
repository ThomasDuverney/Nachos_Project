#include "userfilesys.h"

#ifdef FILESYS

extern void do_UserCreateDirectory(){
  int ptrNameDirectory = machine->ReadRegister(4);
  char * nameDirectory = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  copyStringFromMachine(ptrNameDirectory,nameDirectory, MAX_STRING_SIZE);
  fileSystem->CreateDirectory(nameDirectory);
  free(nameDirectory);
}

extern void do_UserChangeDirectoryPath(){
  int ptrNameDirectory = machine->ReadRegister(4);
  char * nameDirectory = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  copyStringFromMachine(ptrNameDirectory,nameDirectory, MAX_STRING_SIZE);
  fileSystem->ChangeDirectory(nameDirectory);
  free(nameDirectory);
}

extern void do_UserListDirectory(){
  int ptrName= machine->ReadRegister(4);
  char * name = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  copyStringFromMachine(ptrName,name, MAX_STRING_SIZE);
  fileSystem->ListDirectory(name);
  free(name);
}

extern void do_UserRemove(){
  int ptrName= machine->ReadRegister(4);
  char * name = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  copyStringFromMachine(ptrName,name, MAX_STRING_SIZE);
  int checkBool = fileSystem->Remove(name);
  machine->WriteRegister(2,checkBool);
  free(name);
}

extern void do_UserCreate(){
  int checkBool;
  int ptrName = machine->ReadRegister(4);
  int initialSize = machine->ReadRegister(5);
  char * name = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  copyStringFromMachine(ptrName,name, MAX_STRING_SIZE);
  checkBool = fileSystem->Create(name,initialSize);
  machine->WriteRegister(2,checkBool);
  free(name);
}

extern void do_UserOpen(){
  int returnFd;
  int ptrName = machine->ReadRegister(4);
  char * name = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  copyStringFromMachine(ptrName,name, MAX_STRING_SIZE);
  returnFd = fileSystem->OpenFd(name);
  machine->WriteRegister(2,returnFd);
  free(name);
}

extern void do_UserClose(){
  int fileId = machine->ReadRegister(4);
  fileSystem->CloseFd(fileId);
}

extern void do_UserRead(){
  int ptrBuffer = machine->ReadRegister(4);
  int numBytes = machine->ReadRegister(5);
  int fileId = machine->ReadRegister(6);
  int numBytesRead;
  int i = 0;
  char * buffer = (char*) malloc(sizeof(char)*numBytes);
  numBytesRead = fileSystem->ReadFd(fileId,buffer,numBytes);
  while(i < numBytes){
    if(!machine->WriteMem(ptrBuffer++, 1, buffer[i++])){
      DEBUG('f', "Error translation virtual address 0x%x.\n", ptrBuffer-1);
    }
  }
  machine->WriteRegister(2,numBytesRead);
  free(buffer);
}

extern void do_UserReadAt(){

}

extern void do_UserWrite(){
  int fileId = machine->ReadRegister(4);
  int ptrBuffer = machine->ReadRegister(5);
  int numBytes = machine->ReadRegister(6);
  char * intoBuffer = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  int numBytesWrited;
  copyStringFromMachine(ptrBuffer,intoBuffer, MAX_STRING_SIZE);
  numBytesWrited = fileSystem->WriteFd(fileId,intoBuffer,numBytes);
  machine->WriteRegister(2,numBytesWrited);
  free(intoBuffer);
}

extern void do_UserWriteAt(){

}

#else

extern void do_UserCreateDirectory(){
	printf("CreateDirectory\n");
}

extern void do_UserChangeDirectoryPath(){
	printf("ChangeDirectory\n");
}

extern void do_UserListDirectory(){
	printf("ListDirectory\n");
}

extern void do_UserRemove(){
	printf("Remove\n");
}

extern void do_UserCreate(){

}

extern void do_UserOpen(){
}
extern void do_UserClose(){
}
extern void do_UserRead(){
}
extern void do_UserReadAt(){
}
extern void do_UserWrite(){
}
extern void do_UserWriteAt(){

}

#endif
