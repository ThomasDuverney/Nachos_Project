#include "userfilesys.h"


extern void do_UserCreateDirectory(char * nameDirectory){
  fileSystem->CreateDirectory(nameDirectory);
}

extern void do_UserChangeDirectoryPath(char * nameDirectory){
  fileSystem->ChangeDirectory(nameDirectory);
}

extern void do_UserListCurrentDirectory(){
  fileSystem->ListCurrentDirectory();
}

extern void do_UserRemove(char * name){
  int checkBool = fileSystem->Remove(name);
  machine->WriteRegister(2,checkBool);
}
