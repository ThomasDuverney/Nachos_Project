#ifndef SYNCHCONSOLE_H
#define SYNCHCONSOLE_H

#include "copyright.h"
#include "utility.h"
#include "console.h"
#include "synch.h"

class SynchConsole {
    public:
        SynchConsole(char *readFile, char *writeFile); // initialize the hardware console device

        ~SynchConsole();                    // clean up console emulation

        /* Écrit le caractère c sur la sortie standard. */
        void SynchPutChar(const char ch);

        /* Lit un caractère depuis l'entrée standard et retourne le caractère lu. */
        char SynchGetChar();

        /* Écrit la chaîne de caractères lue à l'adresse s. */
        void SynchPutString(const char *s);

        /* Lit une chaîne de caractères de longueur maximale égale à n depuis l'entrée standard et
           l'écrit à l'adresse s */
        void SynchGetString(char *s, int n);

        /* Écrit l'entier n sur la sortie standard. */
        void SynchPutInt(int n);

        /* Lit un entier depuis l'entrée standard et l'écrit à l'adresse n */
        void SynchGetInt(int *n);

        /* Vide le contenu de l'entrée standard */
        void Flush();
    private:
        Console *console;
        /* Stuctures de synchronisations pour les appels read() et write() */
        Semaphore *semRead;
        Semaphore *semWrite;
};

#endif // SYNCHCONSOLE_H
