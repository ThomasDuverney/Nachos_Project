// threadtest.cc 
//      Simple test case for the threads assignment.
//
//      Create two threads, and have them context switch
//      back and forth between themselves by calling Thread::Yield, 
//      to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

int entier = 0;

//----------------------------------------------------------------------
// SimpleThread
//      Loop 5 times, yielding the CPU to another ready thread 
//      each iteration.
//
//      "which" is simply a number identifying the thread, for debugging
//      purposes.
//----------------------------------------------------------------------

void
SimpleThread (int which)
{
    int num;

    for (num = 0; num < 5; num++)
      {
	  printf ("*** thread %d looped %d times\n", which, num);
	  currentThread->Yield ();
      }
}


//----------------------------------------------------------------------
//MutexThreadTest
//      Loop 5 times, yielding the CPU to another ready thread
//      each iteration.
//
//      "which" is simply a number identifying the thread, for debugging
//      purposes.
//----------------------------------------------------------------------

void MutexThreadTest (int arg){

  for(int i = 0; i<5;i++){
    printf ("*** Le thread %d Valeur de l'entier %d \n",arg,entier);
    entier++;
  }

}

//----------------------------------------------------------------------
// ThreadTest
//      Set up a ping-pong between two threads, by forking a thread 
//      to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void ThreadTest (){

    DEBUG ('t', "Entering SimpleTest\n");


    Thread *t = new Thread ("forked thread");

    t->Fork (MutexThreadTest, 1);
    MutexThreadTest (2);
}
