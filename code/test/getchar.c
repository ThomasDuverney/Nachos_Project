#include "syscall.h"
int main() {
    char c = SynchGetChar();
    PutChar('a');
    PutChar(c);
    PutChar('\n');
    //Halt();
    return(14);
}
