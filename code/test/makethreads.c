#include "syscall.h"

void f(void *arg) {
    PutString("f le print a=");
    PutInt(*(int*)arg);
    PutChar('\n');
    UserThreadExit();

}

void g(void *arg) {
    PutString("g le print a=1\n");
    PutString("g le print a=2\n");
    PutString("g le print a=3\n");
    PutString("g le print a=4\n");
    PutString("g le print a=5\n");
    UserThreadExit();

}

int main() {

    int arg = 5;
    UserThreadCreate(g, &arg);
    UserThreadCreate(f, &arg);
    return 2;
}
