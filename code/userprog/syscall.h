/* syscalls.h
 * 	Nachos system call interface.  These are Nachos kernel operations
 * 	that can be invoked from user programs, by trapping to the kernel
 *	via the "syscall" instruction.
 *
 *	This file is included by user programs and by the Nachos kernel.
 *
 * Copyright (c) 1992-1993 The Regents of the University of California.
 * All rights reserved.  See copyright.h for copyright notice and limitation
 * of liability and disclaimer of warranty provisions.
 */

#ifndef SYSCALLS_H
#define SYSCALLS_H

#include "copyright.h"

/* system call codes -- used by the stubs to tell the kernel which system call
 * is being asked for
 */
#define SC_Halt             0
#define SC_Exit	            1
#define SC_Exec             2
#define SC_Join	            3
#define SC_Create           4
#define SC_Open	            5
#define SC_Read	            6
#define SC_Write            7
#define SC_Close            8
#define SC_Fork	            9
#define SC_Yield            10
#define SC_PutChar          11
#define SC_PutString        12
#define SC_GetChar          13
#define SC_GetString        14
#define SC_PutInt           15
#define SC_GetInt           16
#define SC_UserThreadCreate 17
#define SC_UserThreadExit   18
#define SC_UserThreadJoin   19
#define SC_ForkExec         20
#define SC_MutexCreate      21
#define SC_MutexLock        22
#define SC_MutexUnlock      23
#define SC_MutexDestroy     24
#define SC_SemCreate        25
#define SC_SemWait          26
#define SC_SemPost          27
#define SC_SemDestroy       28
#define SC_CondCreate       29
#define SC_CondWait         30
#define SC_CondSignal       31
#define SC_CondBroadCast    32
#define SC_CondDestroy      33
#define SC_CreateDirectory  34
#define SC_ChangeDirectoryPath  35
#define SC_ListDirectory		36
#define SC_Remove               37
#define SC_SendMessage          38
#define SC_ReceiveMessage       39
#define SC_ReadAt               40
#define SC_WriteAt              41

#ifdef IN_USER_MODE

// LB: This part is read only on compiling the test/*.c files.
// It is *not* read on compiling test/start.S


/* The system call interface.  These are the operations the Nachos
 * kernel needs to support, to be able to run user programs.
 *
 * Each of these is invoked by a user program by simply calling the
 * procedure; an assembly language stub stuffs the system call code
 * into a register, and traps to the kernel.  The kernel procedures
 * are then invoked in the Nachos kernel, after appropriate error checking,
 * from the system call entry point in exception.cc.
 */

/* Stop Nachos, and print out performance stats */
void Halt () __attribute__((noreturn));


/* Address space control operations: Exit, Exec, and Join */

/* This user program is done (status = 0 means exited normally). */
void Exit (int status) __attribute__((noreturn));

/* A unique identifier for an executing user program (address space) */
typedef int SpaceId;

/* Run the executable, stored in the Nachos file "name", and return the
 * address space identifier
 */
SpaceId Exec (char *name);

/* Only return once the the user program "id" has finished.
 * Return the exit status.
 */
int Join (SpaceId id);


/* File system operations: Create, Open, Read, Write, Close
 * These functions are patterned after UNIX -- files represent
 * both files *and* hardware I/O devices.
 *
 * If this assignment is done before doing the file system assignment,
 * note that the Nachos file system has a stub implementation, which
 * will work for the purposes of testing out these routines.
 */

/* A unique identifier for an open Nachos file. */
typedef int OpenFileId;

/* when an address space starts up, it has two open files, representing
 * keyboard input and display output (in UNIX terms, stdin and stdout).
 * Read and Write can be used directly on these, without first opening
 * the console device.
 */

#define ConsoleInput	0
#define ConsoleOutput	1

/* Create a Nachos file, with "name" */
void Create (char *name, int initialSize);

/* Open the Nachos file "name", and return an "OpenFileId" that can
 * be used to read and write to the file.
 */
OpenFileId Open(char *name);
/*
 * Sémantique: Écrit "size" octets depuis le fichier dont le descripteur est "id"
 * dans le buffer "buffer".
 * Pré-condition: Le descripteur doit être valide (fichier ouvert), initialisé dans le thread appellant
 * par la méthode Open. Tenter d'écrire dans un fichier non initialisé par open résulte en un comportement non   * spécifié.
 */
void Write (char *buffer, int size, OpenFileId id);

int WriteAt(OpenFileId fd, char* from, int numBytes, int position);

/*
 * Sémantique: Lit "size" octets depuis le fichier dont le descripteur est "id" dans le buffer
 * "buffer". Si le fichier contient moins de "size" octets on lit tout les octets disponibles.
 * Valeur de retour: Nombre d'octets lus.
 * Pré-condition: Le descripteur doit être valide (fichier ouvert), initialisé dans le thread appelant
 * par la méthode Open. Tenter d'écrire dans un fichier non initialisé par open résulte en un comportement non
 * spécifié.
 */
int Read(char *buffer, int size, OpenFileId id);

int ReadAt(OpenFileId id,char * into, int numBytes, int position);
/*
 * Sémantique: Ferme le ficher dont le descripteur est "id".
 * Pré-condition: Le descripteur doit être valide (fichier ouvert), initialisé dans le thread appelant
 * par la méthode Open. Tenter d'écrire dans un fichier non initialisé par open résulte en un comportement non spécifié.
 */
void Close(OpenFileId id);

/* User-level thread operations: Fork and Yield.  To allow multiple
 * threads to run within a user program.
 */

/* Fork a thread to run a procedure ("func") in the *same* address space
 * as the current thread.
 */
void Fork (void (*func) ());

/* Yield the CPU to another runnable thread, whether in this address space
 * or not.
 */
void Yield ();

/*
 * void PutChar(char c)
 * Sémantique: Ecrit le caractère c sur la sortie standard.
 */
void PutChar(char c);

/* void PutString(const char *s)
 * Sémantique: Ecrit la chaîne de caractères lue à l'adresse s, sur la sortie standard.
 */
void PutString(const char *s);

/*
 * char GetChar()
 * Sémantique: Lit un caractère depuis l'entrée standard.
 */
char GetChar();

/*
 * void GetString(char *s, int n)
 * Sémantique:
 *   Lit une chaine de caractères de longueur maximale égale à n depuis l'entrée standard et
 *   l'ecrit à l'adresse de s.
 * Pré-condition:
 *   L'adresse s fournie en paramètre pointe une zone mémoire suffisament large pour stocker
 *   n caractères.
 */
void GetString(char *s, int n);

/*
 * void PutInt(int n)
 * Sémantique: Ecrit l'entier n sur la sortie standard.
 */
void PutInt(int n);

/*
 * void GetInt(int *n)
 * Sémantique: Lit un entier depuis l'entrée standard et l'écrit à l'adresse n.
 * Pré-condition: n doit être un pointeur vers un emplacement mémoire assez large pour stocker un entier.
 */
void GetInt(int *n);

/*
 * int UserThreadCreate(void f(void* arg), void* arg)
 * Spécifications: Prends en paramètres un pointeur de fonction f de valeur de retour
 *   void et un pointeur arg.
 * Sémantique: Crée un nouveau thread utilisateur qui éxécute la fonction f(arg).
 * Pré-Conditions: Le système doit disposer d'une quantité de mémoire suffisante pour allouer la
 *   pile du thread à créer, dans le cas contraire le système s'arrete avec le message:
 *   La création du thread a échoué.
 * Valeur de retour: retourne le champ Id du thread crée. -1 si une erreur s'est produite lors de
 *   la création.
 */
int UserThreadCreate(void f(void* arg), void* arg);

/*
 * void UserThreadExit()
 * Sémantique: Termine le threadUser courant.
 * Post-condition: L'espace mémoire du threadUser est libéré.
 */
void UserThreadExit();

/*
 * int UserThreadJoin(int tid)
 * Sémantique:
 *   Attends la terminaison du threadUser d'id tid, renvoie -1
 si le thread est déjà terminé ou déjà attendu, 0 sinon.
*/
int UserThreadJoin(int tid);

/*
 * int ForkExec(char * fileName)
 * Sémantique:
 *   Crée un nouveau processus qui éxécute le fichier donné en paramètre
 */
int ForkExec(char * fileName);

typedef int Mutex_t;

/*
 * Mutex_t MutexCreate()
 * Sémantique: Crée un mutex et retourne un numéro d'identifiant
 */

Mutex_t MutexCreate();

/*
 * void MutexLock(Mutex_t mutex)
 * Sémantique: Acquiert le vérrou dont l'identifiant est mutexId
 */
void MutexLock(Mutex_t mutex);


/*
 * void MutexUnlock(Mutex_t mutex)
 * Sémantique: Relache le vérrou dont l'identifiant est mutexId
 */
void MutexUnlock(Mutex_t mutex);

/*
 * void MutexDestroy(Mutex_t mutex)
 * Sémantique: Détruit le vérrou dont l'identifiant est mutexId
 */
void MutexDestroy(Mutex_t mutex);

typedef int Sem_t;

/*
 * Sem_t SemCreate()
 * Sémantique: Crée une sémaphore avec une valeur de jeton
 * et retourne un numéro d'identifiant
 */
Sem_t SemCreate(int initialValue);

/*
 * void SemWait(Sem_t semaphore)
 * Sémantique: Décrémente la valeur du jeton
 */
void SemWait(Sem_t semaphore);

/*
 * void SemPost(Sem_t semaphore)
 * Sémantique: Incrémente la valeur du jeton
 */
void SemPost(Sem_t semaphore);

/*
 * void MutexDestroy(Mutex_t mutex)
 * Sémantique: Détruit la sémaphore dont l'identifiant est passé en paramètre
 */
void SemDestroy(Sem_t semaphore);

typedef int Cond_t;

/*
 * Cond_t CondCreate()
 * Sémantique: Crée une condition et retourne un numéro d'identifiant
 */
Cond_t CondCreate();

/*
 * Cond_t CondWait()
 * Précondition : Le mutex doit être vérouiller par le thread appellant
 *                avant d'appeller cette prémitive.
 *
 * Sémantique: Relache le verrou d'identifiant "mutexId" et place le thread
 *             appellant dans la file d'attente de la condition "condId".
 *             Puis endort le thread.
 */
void CondWait(Cond_t condId, Mutex_t mutexId);

/*
 * void CondSignal(Cond_t condId)
 * Sémantique: Réveille un thread en attente sur la condition "condId"et le sort de la file d'attente
 */
void CondSignal(Cond_t condId);

/*
 * void CondBroadCast(Cond_t condId)
 * Sémantique: Réveille et sort tout les threads en attente sur la condition "conId"
 */
void CondBroadCast(Cond_t condId);

/*
 * void MutexDestroy(Mutex_t mutex)
 * Sémantique: Détruit la condition dont l'identifiant est passé en paramètre
 */
void CondDestroy(Cond_t condId);

/*
 * void CreateDirectory(char * name);
 * Sémantique: Créer un répertoire dans le système de fichier Nachos, de nom "name"
               passé en paramètre.
 */
void CreateDirectory(char * name);

void ChangeDirectoryPath(char * name);

/*
 * void ListDirectory(char * name);
 * Sémantique: Liste tout les fichiers et documents du chemin passé en paramètre
 */
void ListDirectory(char * name);

/*
 * int Remove(char * name);
 * Sémantique: Supprime le fichier ou repertoire passé en paramètre
 * Valeur de retour: 1 si la suppréssion a réussi, 0 sinon.
 */
int Remove(char * name);

/*
 * void SendMessage(int addressDesti, int boxTo, int boxFrom, char * data);
 * Sémantique: Envoi du message "data" depuis la boite
 * "boxfrom" vers la machine d'adresse "addressDesti" dans la boite "boxTo"
 */
void SendMessage(int addressDesti, int boxTo, int boxFrom, char * data);

/*
 * void ReceiveMessage(char * data, int box);
 * Sémantique: Initialise la réception d'un message depuis la boite "box".
 * Les données reçues sont stoquées à l'adresse "data".
 */
void ReceiveMessage(char * data, int box);

#endif // IN_USER_MODE

#endif /* SYSCALL_H */
