#include "syscall.h"

int main(){
  CreateDirectory("dossier_temp");
  ChangeDirectoryPath("dossier_temp");
  ListCurrentDirectory();
  ChangeDirectoryPath("..");
  Remove("dossier_temp");
  ListCurrentDirectory();
  return 0;
}
