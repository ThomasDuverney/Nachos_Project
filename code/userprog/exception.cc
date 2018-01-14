// exception.cc
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "userthread.h"
#include "userprocess.h"
#include "usersynchro.h"
void copyStringFromMachine(int from, char *to, unsigned size){
    unsigned int i=0;
    int c;
    while(i<(size-1) && machine->ReadMem(from+i, 1, &c) && (char)c != '\0') {
        *(to+i) = (char)c;
        i++;
    }
    *(to+i) = '\0';
}

//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void UpdatePC (){
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions
//      are in machine.h.
//----------------------------------------------------------------------

void ExceptionHandler (ExceptionType which){
    int type, reg4, reg5;
    type = machine->ReadRegister (2);
    reg4 = machine->ReadRegister (4);
    reg5 = machine->ReadRegister (5);
    char c;
    char * buff;

    if (which == SyscallException) {
        switch (type) {
            case SC_Halt:
                DEBUG('a', "Shutdown, initiated by user program.\n");
                interrupt->Halt();
                break;
            case SC_PutChar:
                DEBUG('a', "PutChar, initiated by user program.\n");
                synchconsole->SynchPutChar((char)reg4);
                break;
            case SC_PutString:
                DEBUG('a', "SynchPutString, initiated by user program.\n");
                char buf [MAX_STRING_SIZE];
                copyStringFromMachine(reg4, buf, MAX_STRING_SIZE);
                synchconsole->SynchPutString(buf);
                break;
            case SC_GetChar:
                DEBUG('a', "GetChar, initiated by user program.\n");
                c = synchconsole->SynchGetChar();
                machine->WriteRegister(2, (int)c);
                break;
            case SC_GetString:
                DEBUG('a', "SynchGetString, initiated by user program.\n");
                // reg4 = adresse du tableau de la string (memoire virtuelle)
                // reg5 = taille max
                // On écrit la valeur de GetString en mémoire
                buff = (char*) malloc(reg5 * sizeof(char));
                synchconsole->SynchGetString(buff, reg5);
                int h;
                h = 0;
                while(h < reg5){
                    if(!machine->WriteMem(reg4++, 1, buff[h++])){
                      DEBUG('f', "Error translation virtual address 0x%x.\n", reg4-1);
                    }
                }
                free(buff);
                break;
            case SC_PutInt:
                DEBUG('a', "SynchPutInt, initiated by user program.\n");
                synchconsole->SynchPutInt(reg4);
                break;
            case SC_GetInt:
                DEBUG('a', "SynchGetInt, initiated by user program.\n");
                int val;
                synchconsole->SynchGetInt(&val);
                machine->WriteMem(reg4, 4, val);
                break;
            case SC_UserThreadCreate:
                DEBUG('a', "UserThreadCreate, initiated by user program.\n");
                int threadId;
                threadId = do_UserThreadCreate(reg4, reg5);
                // /!\ ATTENTION TRAITER LE CAS OU LE THREADID = -1
                machine->WriteRegister(2,threadId);
                break;
            case SC_UserThreadExit:
                DEBUG('a', "UserThreadExit, initiated by user program.\n");
                do_UserThreadExit();
                break;
            case SC_UserThreadJoin:
                DEBUG('a', "UserThreadJoin, initiated by user program.\n");
                int returnValue;
                returnValue = do_UserThreadJoin(reg4);
                machine->WriteRegister(2,returnValue);
                break;
            case SC_Exit:
                DEBUG('a', "Exit, initiated by user program.\n");
                currentThread->Finish();
                break;
            case SC_ForkExec:
                DEBUG('a', "Syscall ForkExec");
                char * executableName;
                executableName = (char *) malloc(sizeof(char)*MAX_STRING_SIZE);
                copyStringFromMachine(reg4, executableName, MAX_STRING_SIZE);
                do_UserProcessCreate(executableName);
                break;
            case SC_MutexCreate:
                do_UserMutexCreate();
                break;
            case SC_MutexLock:
                do_UserMutexLock();
                break;
            case SC_MutexUnlock:
                do_UserMutexUnlock();
                break;
            case SC_MutexDestroy:
                do_UserMutexDestroy();
                break;
            default:
                printf("Unexpected user mode exception %d %d\n", which, type);
                ASSERT(FALSE);
        }
    }

    // LB: Do not forget to increment the pc before returning!
    UpdatePC();
    // End of addition
}
