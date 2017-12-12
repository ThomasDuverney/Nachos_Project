#include "syscall.h"

int print(char c, int n) {
    int i;
    for (i = 0; i < n; i++) {
        PutChar(c+i);
    }
    PutChar('\n');
    return (3);
}

int main() {
    int i = print('a',4);
    PutChar(i);
    PutChar('\n');
    PutChar('a');
    //Halt();
    return(14);
}
