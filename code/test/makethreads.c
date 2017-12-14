#include "syscall.h"

void f(void *arg) {
    PutString("f le print a=");
    PutInt(*(int*)arg);
    PutChar('\n');
}

int main() {
    PutString("Debut makethreads\n");
    int arg = 5;
    int ret = UserThreadCreate(f, &arg);
    PutString("Fin makethread ret=");
    PutInt(ret);
    PutChar('\n');
    return(0);
}
