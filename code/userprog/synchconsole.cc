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
    while(s[i] != '\0' && s[i] != EOF && s[i] != 04){
        console->PutChar(s[i]);
        writeDone->P();
        i++;
    }
    semWrite->V();
}

void SynchConsole::SynchGetString(char *s, int n) {
    semRead->P();
    int i = 0;
    char c;
    bool continuer = true;

    while(i<n && continuer == true){
        readAvail->P();
        c = console->GetChar();
        if (c == EOF || c == 04 || c == '\n' || c == '\0'){
            s[i] = '\0';
            /* On s'arrète quand on trouve un caractère de fin de séquence */
            continuer = false;
        }
        s[i] = c;
        i++;
    }
    /* A la sortie on a soit i == n soit un caractère de fin de séquence a été lu */
    if (i == n){
        s[i] = '\0';
        /*
         Flush l'entrée standard si la taille de la chaine en entrée dépasse n.
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
    readAvail->P();
    c = console->GetChar();
    while(c != EOF && c != 04 && c != '\n') {
        readAvail->P();
        c = console->GetChar();
    }
}
