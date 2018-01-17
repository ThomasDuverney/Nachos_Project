/*
 * Structure pour le passage d'une fonction et ses paramètres lors de la création
 * d'un thread utilisateur.
 */
typedef struct _userThreadParams {
  int f;
  int arg;
  int addrExit;
}UserThreadParams;

/*
 * Specification: int do_UserThreadCreate(int f, int arg)
 *   Prends en paramètres l'adresse d'une fonction f et l'adresse des paramètres de la fonction.
 * Sémantique:
 *   Crée un thread noyau (propulseur) qui permet le lancement d'un thread utilisateur exécutant la fonction
 *   dont l'adresse est f et dont les paramètres sont fournis à l'adresse arg.
 * Valeur de retour:
 *   l'adresse du thread propulseur, NULL si la création du thread a échoué.
 */
extern void do_UserThreadCreate();

/*
 * Spécification: extern void do_UserThreadExit()
 * Sémantique:
 * Lorsqu'un Thread T termine, il regarde si des Threads Ti l'attendent.
 * Avant de quitter le thread courant remet les éventuels Ti en sommeil dans la ready list du scheduler.
 */
extern void do_UserThreadExit();

/*
 * Spécification: extern int do_UserThreadJoin(int tid)
 * Sémantique: Lorsqu'un Thread T1 fait un join sur un Thread T2 on ajoute dans la map
 * T1->space->joinMap l'association (T2.Tid, [T1]).
 * Ainsi on sait que T2 est attendu par T1.
 * Un thread ne peut join un autre thread que si il est vivant (présent dans threadList de l'addrspace)
 */
extern void do_UserThreadJoin();
