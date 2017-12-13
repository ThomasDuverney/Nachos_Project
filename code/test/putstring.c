#include "syscall.h"

int main() {
    char s[] = {"ABCDEFGHIJKLMNOPQ"};
    PutString(s);
    Halt();
}
