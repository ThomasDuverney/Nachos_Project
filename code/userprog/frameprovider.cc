#include "frameprovider.h"
#include "system.h"
#include "stdlib.h"


FrameProvider::FrameProvider(){
  bitmap = new BitMap(NumPhysPages);
  bzero(machine->mainMemory,MemorySize);
}

FrameProvider::~FrameProvider(){
  delete bitmap;
}

int FrameProvider::GetEmptyFrame() {
  int index = bitmap->Find();
  /* On vérifie qu'on ai bien trouvé un cadre de page libre */
  ASSERT(index != -1);

  return index;
}

int FrameProvider::GetEmptyFrameRandom(){
  int sizeFree = bitmap->NumClear();
  int *freeFrameArray;
  int indexArray, indexBitmap, indexFree;

  ASSERT(sizeFree > 0);

  freeFrameArray = (int *) malloc(sizeFree * sizeof(int));

  indexArray = 0;
  indexBitmap = 0;

  while(indexArray < sizeFree){

    /* Si le cadre de page d'index "indexbitmap" est libre on l'ajoute dans le tableau freeFrameArray */
    if(bitmap->Test(indexBitmap) == FALSE){
      freeFrameArray[indexArray] = indexBitmap;
      indexArray++;
    }
    indexBitmap++;
  }

  /* Choix aléatoire dans freeFrameArray d'un index de cadre de page libre */
  indexFree = freeFrameArray[random() % sizeFree];
  bitmap->Mark(indexFree);
  free(freeFrameArray);
  return indexFree;

}

void FrameProvider::ReleaseFrame(int pageNum) {
  ASSERT(pageNum >= 0 && pageNum < NumPhysPages);
  bitmap->Clear(pageNum);
}

int FrameProvider::NumAvailableFrame() {
  return bitmap->NumClear();
}
