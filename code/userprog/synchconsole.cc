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

void SynchConsole::SynchPutString(const char *s) {
    semWrite->P();
    int i=0;
    while(s[i] != '\0'){
        console->PutChar(s[i++]);
        writeDone->P();
    }
    semWrite->V();
}

void SynchConsole::SynchGetString(char *s, int n) {
    semRead->P();
    int i = 0;
    char c;
    bool sequenceEnd = false;

    while(i<(n-1) && !sequenceEnd){
        readAvail->P();
        c = console->GetChar();

        if (c == EOF || c == 04 || c == '\n'){
            s[i] = '\0';
            sequenceEnd = true;
        }
        s[i] = c;
        i++;
    }
    if (i == (n-1)){
        s[i] = '\0';
        /*
         Va Flush l'entrée standard si on essaye de dépasser (Sécurité)
         Ne marche surrement pas avec un fichier en entrée
        */
        Flush();
    }
    semRead->V();
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
