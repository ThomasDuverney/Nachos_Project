extern void do_UserMutexCreate();
extern void do_UserMutexLock();
extern void do_UserMutexUnlock();
extern void do_UserMutexDestroy();


////////////////////////////////////////////////////////
//           Gestion des  Sémaphores utilisateur      //
//                                                    //
////////////////////////////////////////////////////////

extern void do_UserSemInit();
extern void do_UserSemWait();
extern void do_UserSemPost();
extern void do_UserSemDestroy();
