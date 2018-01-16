#include "userfilesys.h"

#ifdef FILESYS

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