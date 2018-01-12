/*
 * Structure pour le passage d'une fonction et ses paramètres lors de la création
 * d'un thread utilisateur.
 */
typedef struct _userThreadParams{
  int f;
  int arg;
}UserThreadParams;

/* int do_UserThreadCreate(int f, int arg):
 * Specification:
 *   Prends en paramètres l'adresse d'une fonction f et l'adresse des paramètres de la fonction.
 * Sémantique:
 *   Crée un thread noyau (propulseur) qui permet le lancement d'un thread utilisateur exécutant la fonction
 *   dont l'adresse est f et dont les paramètres sont fournis à l'adresse arg.
 * Valeur de retour:
 *   l'adresse du thread propulseur, NULL si la création du thread a échoué.
 */
extern int do_UserThreadCreate(int f, int arg);

/* static void StartUserThread(int UserThreadParams)
 * Spécification:
 *   Prends en paramètres l'adresse d'une structure Userthreadparams.
 * Sémantique:
 *   Lance un thread utilisateur qui éxécute la fonction UserThreadParams->f prennant comme
 *   arguments UserThreadparams->arg.
 */
//static void StartUserThread(int UserThreadParams);

/*
 *
 */
extern void do_UserThreadExit();

/*
 *
 */
//extern int do_UserThreadJoin(int tid);
