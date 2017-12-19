#include "copyright.h"
#include "system.h"
#include "synchconsole.h"

static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile) {
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    semRead = new Semaphore("read", 1);
    semWrite = new Semaphore("write", 1);
    console = new Console(readFile, writeFile, ReadAvail, WriteDone, 0);
}

SynchConsole::~SynchConsole() {
    delete console;
    delete writeDone;
    delete readAvail;
    delete semRead;
    delete semWrite;
}

void SynchConsole::SynchPutChar(const char c) {
    semWrite->P();
    console->PutChar(c);
    writeDone->P();
    semWrite->V();
}

char SynchConsole::SynchGetChar() {
    semRead->P();
    readAvail->P();
    char c = console->GetChar();
    semRead->V();
    return c;

}

void SynchConsole::SynchPutString(const char s[]) {
    int i=0;
    while(s[i] != '\0'){
        SynchPutChar(s[i++]);
    }
}

void SynchConsole::SynchGetString(char *s, int n) {
    int i;
    char c;
    for(i=0; i<(n-1); i++){
        c = SynchGetChar();

        if (c == EOF || c == 04 || c == '\n'){
            s[i] = '\0';
            return;
        }
        s[i] = c;
    }
    if (i == (n-1)){
        s[i] = '\0';
    }
}

void SynchConsole::SynchPutInt(int n){
    char str [MAX_STRING_SIZE];
    sprintf(str, "%d", n);
    SynchPutString(str);
}

void SynchConsole::SynchGetInt(int *n){
    char str [MAX_STRING_SIZE];
    SynchGetString(str, MAX_STRING_SIZE);
    sscanf(str, "%d", n);
}

void SynchConsole::Flush(){
    char c;
    while((c = SynchGetChar()) != EOF && c != 04 && c != '\n');
}
