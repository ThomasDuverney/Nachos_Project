#include "syscall.h"

int main(){
  CreateDirectory("dossier_temp");
  ChangeDirectoryPath("dossier_temp");
  ListDirectory(".");
  ChangeDirectoryPath("..");
  Remove("dossier_temp");
  ListDirectory(".");
  return 0;
}
