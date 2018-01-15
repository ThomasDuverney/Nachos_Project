extern void do_UserMutexCreate();
extern void do_UserMutexLock();
extern void do_UserMutexUnlock();
extern void do_UserMutexDestroy();


////////////////////////////////////////////////////////
//           Gestion des  Sémaphores utilisateur      //
//                                                    //
////////////////////////////////////////////////////////

extern void do_UserSemCreate();
extern void do_UserSemWait();
extern void do_UserSemPost();
extern void do_UserSemDestroy();

////////////////////////////////////////////////////////
//           Gestion des conditions mutex             //
//                utilisateur                         //
////////////////////////////////////////////////////////

extern void do_UserCondCreate();
extern void do_UserCondWait();
extern void do_UserCondSignal();
extern void do_UserCondBroadCast();
extern void do_UserCondDestroy();
