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


static void ReadAtVirtual(OpenFile *executable, int virtualaddr, int numBytes, int position, TranslationEntry *pageTable, unsigned numPages);

//----------------------------------------------------------------------
// SwapHeader
//      Do little endian to big endian conversion on the bytes in the
//      object file header, in case the file was generated on a little
//      endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------

static void
SwapHeader (NoffHeader * noffH)
{
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

AddrSpace::AddrSpace (OpenFile * executable)
{

    NoffHeader noffH;
    unsigned int i, size, numPagesPerAddrSpace, numStackPerAddrSpace;

    executable->ReadAt ((char *) &noffH, sizeof (noffH), 0);
    // ReadAtVirtual(executable, (char *) &noff, sizeof(noff), 0, machine->pageTable, machine->pageTableSize);
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
	  pageTable[i].physicalPage = i;
	  pageTable[i].valid = TRUE;
	  pageTable[i].use = FALSE;
	  pageTable[i].dirty = FALSE;
	  pageTable[i].readOnly = FALSE;	// if the code segment was entirely on
	  // a separate page, we could set its
	  // pages to be read-only
      }

      machine->pageTable = pageTable;
      machine->pageTableSize = numPages;

// zero out the entire address space, to zero the unitialized data segment
// and the stack segment
    bzero (machine->mainMemory, size);

// then, copy in the code and data segments into memory
    if (noffH.code.size > 0)
      {
	  DEBUG ('a', "Initializing code segment, at 0x%x, size %d\n",
		 noffH.code.virtualAddr, noffH.code.size);

    //// MODIFICATION ReadAtVirtual


    ReadAtVirtual(executable, noffH.code.virtualAddr, noffH.code.size, noffH.code.inFileAddr, machine->pageTable, machine->pageTableSize);

	  //executable->ReadAt (&(machine->mainMemory[noffH.code.virtualAddr]),
		//	      noffH.code.size, noffH.code.inFileAddr);
      }
    if (noffH.initData.size > 0){
    DEBUG ('a', "Initializing data segment, at 0x%x, size %d\n",
    noffH.initData.virtualAddr, noffH.initData.size);
    /*executable->ReadAt (&
          (machine->mainMemory
           [noffH.initData.virtualAddr]),
          noffH.initData.size, noffH.initData.inFileAddr);*/
        ReadAtVirtual(executable, noffH.initData.virtualAddr, noffH.initData.size, noffH.initData.inFileAddr, machine->pageTable, machine->pageTableSize);
    }

      //// Allocation de(s) page(s) pour les threads 

      // Nombre de pages dans l'espage d'adressage libre après les zones initdata et uninitdata
      numPagesPerAddrSpace = divRoundDown(UserStackSize, PageSize);
      // Nombre de piles que l'on peut stoquer dans l'espace disponible
      numStackPerAddrSpace = divRoundDown(numPagesPerAddrSpace, NumPagesPerStack);
      // Tableau des emplacement pour piles disponibles.
      stackBitmap = new BitMap(numStackPerAddrSpace);
      // Le main occupe le première emplacement de pile. 
      stackBitmap->Mark(0);
}

//----------------------------------------------------------------------
// AddrSpace::~AddrSpace
//      Dealloate an address space.  Nothing for now!
//----------------------------------------------------------------------

AddrSpace::~AddrSpace ()
{
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

void
AddrSpace::InitRegisters ()
{
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

void
AddrSpace::SaveState ()
{
}

//----------------------------------------------------------------------
// AddrSpace::RestoreState
//      On a context switch, restore the machine state so that
//      this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------

void
AddrSpace::RestoreState ()
{
    machine->pageTable = pageTable;
    machine->pageTableSize = numPages;
}


//----------------------------------------------------------------------
// ReadAtVirtual
//      Lit dans le disque physique numBytes à la bonne position,
//      puis le stocke dans l'adresse virtuel grâce à la TLB,
//
//  "executable" -- objet openfile qui contient l'executable et permet
//          d'utiliser ReadAt 
//  "virtualaddr" -- adresse virtuelle
// PAS FINI
//----------------------------------------------------------------------


static void ReadAtVirtual(OpenFile *executable, int virtualaddr, int numBytes, int position, TranslationEntry *pageTable, unsigned numPages){
    char buff[numBytes];
    int nbRead;
    int i;
    unsigned int index_table;

    // ASSERT(numBytes > PageSize);


    //  on rempli le buffer
    nbRead = executable->ReadAt(buff, numBytes, position);


    index_table = (unsigned) virtualaddr / PageSize;

    ASSERT(numPages >= index_table);

    // on écrit dans la mémoire
    //// IL FAUT FAIRE UN DECALAGE DE L'ADRESSE VIRTUELLE
    //// CAR ON ECRIT TOUJOURS AU MEME ENDROIT
    i = 0;
    while(i < nbRead){
        if(nbRead - i < 4 && nbRead - i >= 2 ){

            if(!machine->WriteMem(virtualaddr, 2, buff[i])){
                DEBUG('f', "Error translation virtual address 0x%x.\n", virtualaddr);
            }
            i += 2;
            virtualaddr = (int)(((char *)virtualaddr) + 2);

        } else if(nbRead - i < 2) {
            if(!machine->WriteMem(virtualaddr, 1, buff[i])){
                DEBUG('f', "Error translation virtual address 0x%x.\n", virtualaddr);
            }
            i += 1;
            virtualaddr = virtualaddr << 1;
            virtualaddr = (int)(((char *)virtualaddr) + 1);
        } else {
            if(!machine->WriteMem(virtualaddr, 4, buff[i])){
                DEBUG('f', "Error translation virtual address 0x%x.\n", virtualaddr);
            }
            i += 4;
            virtualaddr = (int)(((char *)virtualaddr) + 4);
        }

    }

    // on récupère l'indice dans la table des pages


    // mise a jour des flags
    pageTable[index_table].valid = FALSE;
    pageTable[index_table].use = TRUE;
    // Flag dirty mis à jour par machine->Translate

}

