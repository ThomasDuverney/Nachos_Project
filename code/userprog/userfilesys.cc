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

extern void do_UserListCurrentDirectory(){
  fileSystem->ListCurrentDirectory();
}

extern void do_UserRemove(){
  int ptrName= machine->ReadRegister(4);
  char * name = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
  copyStringFromMachine(ptrName,name, MAX_STRING_SIZE);
  int checkBool = fileSystem->Remove(name);
  machine->WriteRegister(2,checkBool);
}

#else

extern void do_UserCreateDirectory(char * nameDirectory){
	printf("CreateDirectory\n");
}

extern void do_UserChangeDirectoryPath(char * nameDirectory){
	printf("ChangeDirectory\n");
}

extern void do_UserListCurrentDirectory(){
	printf("ListCurrentDirectory\n");
}

extern void do_UserRemove(char * name){
	printf("Remove\n");
}

#endif
