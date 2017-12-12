#include "syscall.h"

int main() {
    char s[] = {"ABCDEFGHIJKLMNOPQ"};
    SynchPutString(s);
    Halt();
}
