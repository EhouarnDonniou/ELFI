#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"

void main(){
    char* ficmai = "../TP1/fichiers-de-maillage-tests/car1x1q_4";
    float** coord;
    int** ngnel; 
    int** nRefAr;
    int typel, nbtng, nbtel, nbneel, nbaret;
    lecfima(ficmai,&typel,&nbtng,&coord,&nbtel,&ngnel, &nbneel, &nbaret, &nRefAr);

    //Allocation de MatElem, SMbrElem, NuDElem et uDElem
    float** MatElem=alloctab(nbneel,nbneel);
    float* SMbrElem=calloc(nbneel,sizeof(float));
    float* NuDElem=calloc(nbneel,sizeof(float));
    float* uDElem=calloc(nbneel,sizeof(float));
    //Initialisation à 0 des --Elem
    for(int i=0; i<nbneel ; i++){
        for(int j=0; j<nbneel; j++){
            MatElem[i][j]=0;
        }
    }
    //Boucle sur les éléments K
    for(int i=0;i<k;i++){
        cal1Elem( nRefDom, int nbRefD0, int* numRefD0, int nbRefD1, int* numRefD1, int nbRefF1, int* numRefF1, 
                  int typeEl, int nbneel, float** coorEl, int nbaret, int* nrefArEl,
                  float** MatElem, float* SMbrElem, float* NuDElem, float* uDElemen)
    }
}