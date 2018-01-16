// addrspace.cc
//      Routines to manage address spaces (executing user programs).
//
//      In order to run a user program, you must:
//
//      1. link with the -N -T 0 option
//      2. run coff2noff to convert the object file to Nachos format
//              (Nachos object code format is essentially just a simpler
//              version of the UNIX executable object code format)
//      3. load the NOFF file into the Nachos file system
//              (if you haven't implemented the file system yet, you
//              don't need to do this last step)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "noff.h"
#include <strings.h>		/* for bzero */

/*
 * Spécification:
 * static void ReadAtVirtual(OpenFile *executable, int virtualaddr, int numBytes, int position, TranslationEntry *pageTable, * unsigned numPages)
 * Sémantique: Lit "numbytes" octets dans le fichier "executable" depuis la position "position"
 * et les place en mémoire à l'adresse virtuele "virtualaddr" de la table des pages "pageTable".
 * Pré-conditions: executable est l'adresse d'un fichier valide. La table "pageTable" contient suffisamment de pages pour stocker numBytes.
 */
static void ReadAtVirtual(OpenFile *executable, int virtualaddr, int numBytes, int position, TranslationEntry *pageTable, unsigned numPages) {
    char buff[numBytes];
    int nbRead;
    TranslationEntry * oldTable;
    int i, oldTableSize;

    /* Sauvegarde de l'ancien contexte */
    oldTable = machine->pageTable;
    oldTableSize = machine->pageTableSize;
    machine->pageTable = pageTable;
    machine->pageTableSize =  numPages;

    /* Lit "numbytes" du fichier "executable" depuis la position "position" et les place dans le buffer "buff" */
    nbRead = executable->ReadAt(buff, numBytes, position);
    ASSERT(nbRead == numBytes);
    i = 0;
    while(i < nbRead){
        if(!machine->WriteMem(virtualaddr, 1, buff[i])){
          DEBUG('f', "Error translation virtual address 0x%x.\n", virtualaddr);
        }
        i += 1;
        virtualaddr += 1;
    }

    /* Restauration de l'ancien contexte */
    machine->pageTable = oldTable;
    machine->pageTableSize = oldTableSize;
}

//----------------------------------------------------------------------
// SwapHeader
//      Do little endian to big endian conversion on the bytes in the
//      object file header, in case the file was generated on a little
//      endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------
static void SwapHeader (NoffHeader * noffH) {
    noffH->noffMagic = WordToHost (noffH->noffMagic);
    noffH->code.size = WordToHost (noffH->code.size);
    noffH->code.virtualAddr = WordToHost (noffH->code.virtualAddr);
    noffH->code.inFileAddr = WordToHost (noffH->code.inFileAddr);
    noffH->initData.size = WordToHost (noffH->initData.size);
    noffH->initData.virtualAddr = WordToHost (noffH->initData.virtualAddr);
    noffH->initData.inFileAddr = WordToHost (noffH->initData.inFileAddr);
    noffH->uninitData.size = WordToHost (noffH->uninitData.size);
    noffH->uninitData.virtualAddr =
	WordToHost (noffH->uninitData.virtualAddr);
    noffH->uninitData.inFileAddr = WordToHost (noffH->uninitData.inFileAddr);
}

//----------------------------------------------------------------------
// AddrSpace::AddrSpace
//      Create an address space to run a user program.
//      Load the program from a file "executable", and set everything
//      up so that we can start executing user instructions.
//
//      Assumes that the object code file is in NOFF format.
//
//      First, set up the translation from program memory to physical
//      memory.  For now, this is really simple (1:1), since we are
//      only uniprogramming, and we have a single unsegmented page table
//
//      "executable" is the file containing the object code to load into memory
//----------------------------------------------------------------------
AddrSpace::AddrSpace (OpenFile * executable) {
    NoffHeader noffH;
    unsigned int i, size, numPagesPerAddrSpace, numStackPerAddrSpace;
    /* Lecture du fichier objet depuis le disque dans la structure noff */
    executable->ReadAt ((char *) &noffH, sizeof (noffH), 0);

    if ((noffH.noffMagic != NOFFMAGIC) &&
	(WordToHost (noffH.noffMagic) == NOFFMAGIC))
	SwapHeader (&noffH);
    ASSERT (noffH.noffMagic == NOFFMAGIC);

// how big is address space?
    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size + UserStackSize;	// we need to increase the size
    // to leave room for the stack
    numPages = divRoundUp (size, PageSize);
    size = numPages * PageSize;

    ASSERT (numPages <= NumPhysPages);	// check we're not trying
    // to run anything too big --
    // at least until we have
    // virtual memory

    DEBUG ('a', "Initializing address space, num pages %d, size %d\n",
	   numPages, size);
    // first, set up the translation
    pageTable = new TranslationEntry[numPages];
    for (i = 0; i < numPages; i++)
      {
    	  pageTable[i].virtualPage = i;	// for now, virtual page # = phys page #
          pageTable[i].physicalPage = frameProvider->GetEmptyFrameRandom();
          pageTable[i].valid = TRUE;
    	  pageTable[i].use = FALSE;
    	  pageTable[i].dirty = FALSE;
    	  pageTable[i].readOnly = FALSE;	// if the code segment was entirely on
    	  // a separate page, we could set its
    	  // pages to be read-only
      }

      // zero out the entire address space, to zero the unitialized data segment
      // and the stack segment
      // bzero (machine->mainMemory, size);

    // then, copy in the code and data segments into memory
    if (noffH.code.size > 0){
	  DEBUG ('a', "Initializing code segment, at 0x%x, size %d\n", noffH.code.virtualAddr, noffH.code.size);
      ReadAtVirtual(executable, noffH.code.virtualAddr, noffH.code.size, noffH.code.inFileAddr, pageTable, numPages);
    }

    if (noffH.initData.size > 0){
      DEBUG ('a', "Initializing data segment, at 0x%x, size %d\n", noffH.initData.virtualAddr, noffH.initData.size);
      ReadAtVirtual(executable, noffH.initData.virtualAddr, noffH.initData.size, noffH.initData.inFileAddr, pageTable, numPages);
    }

    /* Allocation de(s) page(s) pour les threads */
    /* Nombre de pages dans l'espage d'adressage libre après les zones initdata et uninitdata */
      numPagesPerAddrSpace = divRoundDown(UserStackSize, PageSize);
      /* Nombre de piles que l'on peut stocker dans l'espace disponible */
      numStackPerAddrSpace = divRoundDown(numPagesPerAddrSpace, NumPagesPerStack);
      /* Tableau des emplacements pour piles disponibles */
      stackBitmap = new BitMap(numStackPerAddrSpace);
      /* Le main occupe le première emplacement de pile */
      stackBitmap->Mark(0);
      /* Initialise la sémaphore pour bloquer la terminaison d'un processus */
      this->nbThread = 1;
      /* init joinMap */
      joinMap = new std::map<int, std::list<Thread*>* >();
      /* init threadList */
      threadList = new std::list<int>();
}

//----------------------------------------------------------------------
// AddrSpace::~AddrSpace
//      Dealloate an address space.  Nothing for now!
//----------------------------------------------------------------------
AddrSpace::~AddrSpace () {
  // LB: Missing [] for delete
  // delete pageTable;
  delete [] pageTable;
  // End of modification
}

//----------------------------------------------------------------------
// AddrSpace::InitRegisters
//      Set the initial values for the user-level register set.
//
//      We write these directly into the "machine" registers, so
//      that we can immediately jump to user code.  Note that these
//      will be saved/restored into the currentThread->userRegisters
//      when this thread is context switched out.
//----------------------------------------------------------------------
void AddrSpace::InitRegisters () {
    int i;
    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister (i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister (PCReg, 0);

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister (NextPCReg, 4);

    // Set the stack register to the end of the address space, where we
    // allocated the stack; but subtract off a bit, to make sure we don't
    // accidentally reference off the end!
    machine->WriteRegister (StackReg, numPages * PageSize - MainGuardOffset);
    DEBUG ('a', "Initializing stack register to %d\n", numPages * PageSize - MainGuardOffset);
}

//----------------------------------------------------------------------
// AddrSpace::SaveState
//      On a context switch, save any machine state, specific
//      to this address space, that needs saving.
//
//      For now, nothing!
//----------------------------------------------------------------------
void AddrSpace::SaveState () {
    pageTable = machine->pageTable;
    numPages = machine->pageTableSize;
}

//----------------------------------------------------------------------
// AddrSpace::RestoreState
//      On a context switch, restore the machine state so that
//      this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------
void AddrSpace::RestoreState () {
    machine->pageTable = pageTable;
    machine->pageTableSize = numPages;
}

TranslationEntry * AddrSpace::getPageTable() {
    return pageTable;
}

unsigned int AddrSpace::getNumPages() {
    return numPages;
}

void AddrSpace::printJoinMap () {
    std::map<int, std::list<Thread*>* >::iterator it;
    printf("\n--------JOINMAP---------\n");
    for (it = joinMap->begin(); it != joinMap->end(); it++ ){
        printf("TID = %d\n",it->first);
        std::list<Thread*>* list = it->second;
        for (std::list<Thread*>::const_iterator iterator = list->begin(), end = list->end(); iterator != end; ++iterator) {
            printf("\tThread = %d\n",(*iterator)->getTid());
        }
    }
}

void AddrSpace::printThreadList () {
    printf("\n--------THREADLIST-----------\n");
    for (std::list<int>::const_iterator iterator = threadList->begin(), end = threadList->end(); iterator != end; ++iterator) {
        printf("\tThread = %d\n",*iterator);
    }
}

void AddrSpace::incrementNbThread() {
  nbThread++;
}

void AddrSpace::decrementNbThread() {
  nbThread--;
}

int AddrSpace::getNbThread() {
  return threadList->size();
}
