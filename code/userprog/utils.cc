#include "utils.h"
extern void copyStringFromMachine(int from, char *to, unsigned size){
  unsigned int i=0;
  int c;
  while(i<(size-1) && machine->ReadMem(from+i, 1, &c) && (char)c != '\0') {
    *(to+i) = (char)c;
    i++;
  }
  *(to+i) = '\0';
}
