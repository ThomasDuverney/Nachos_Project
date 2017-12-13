#include "syscall.h"
int main() {
    char c = GetChar();
    PutChar('|');
    PutChar(c);
    PutChar('|');
    PutInt((int)c);
    PutChar('\n');
    return(14);
}
