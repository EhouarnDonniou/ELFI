#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"

void main(){
    char* ficmai = "../TP1/fichiers-de-maillage-tests/output_maillage.txt";
    float** pcoord;
    int** pngnel; 
    int** pnRefAr;
    int ptypel, pnbtng, pnbtel, pnbneel, pnbaret;

    int lecfima(ficmai,&ptypel,&pnbtng,&pcoord,&pnbtel,&pngnel, &pnbneel, &pnbaret, &pnRefAr);
}