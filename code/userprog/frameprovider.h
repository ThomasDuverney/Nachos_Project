#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H
#include "bitmap.h"

class FrameProvider {

  public:

  FrameProvider();

  ~FrameProvider();
  /*
    GetEmptyFrame
    Spécifications: int GetEmptyFrame()
    Sémantique: retourne l'indice d'un cadre de page physique libre.
    Met à jour la BitMap et marque la page comme occupée.
  */
  int GetEmptyFrame();

  /*
    GetEmptyFrameRandom
    Spécifications: int GetEmptyFrameRandom()
    Sémantique: retourne un indice aléatoire d'un cadre de page physique libre.
    Met à jour la BitMap et marque la page comme occupée.
  */
  int GetEmptyFrameRandom();

  /*
    ReleaseFrame
    Spécifications: void ReleaseFrame( int pageNum)
    Sémantique: Met à jour la Bitmap et libère le cadre physique de page d'indice pageNum
  */
  void ReleaseFrame(int pageNum);

  /*
     NumAvailableFrame
     Spécifications: int NumAvailableFrame()
     Sémantique: Retourne le nombre de cadres de pages libres.
  */
  int NumAvailableFrame();

 private :
  BitMap *bitmap;

};

#endif
