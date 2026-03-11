#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"

void main(){
    //Declaration
    char* ficmai = "../TP1/fichiers-de-maillage-tests/car1x1q_4";
    float** coord;
    int** ngnel; 
    int** nRefAr;
    int typeEl, nbtng, nbtel, nbneel, nbaret, nRefDom, nbRefD0, nbRefD1, nbRefF1;
    int* numRefD0;
    int* numRefD1;
    int* numRefF1;
    int* nrefArEl;
    lecfima(ficmai,&typeEl,&nbtng,&coord,&nbtel,&ngnel, &nbneel, &nbaret, &nRefAr);

    //Allocation
    float** MatElem=alloctab(nbneel,nbneel);
    float* SMbrElem=calloc(nbneel,sizeof(float));
    int* NuDElem=calloc(nbneel,sizeof(int));
    float* uDElem=calloc(nbneel,sizeof(float));
    float** coorEl=alloctab(nbneel,nbneel);

    //Boucle sur les éléments K
    for(int k=0;k<nbtel;k++){
        
        //Initialisation à 0 de MatElem, SMbrElem, NuDElem et uDElem
        for(int i=0; i<nbneel ; i++){
            SMbrElem[i]=0;
            NuDElem[i]=0;
            uDElem[i]=0;
            for(int j=0; j<nbneel; j++){
            MatElem[i][j]=0;
            }
        }
        selectPts(nbneel,ngnel[k],coord,coorEl);
        cal1Elem(nRefDom, nbRefD0, numRefD0, nbRefD1, numRefD1, nbRefF1, numRefF1, 
                  typeEl, nbneel, coorEl, nbaret, nrefArEl,
                  MatElem, SMbrElem, NuDElem, uDElem);

        impCalEl(k, typeEl, nbneel, MatElem, SMbrElem, NuDElem, uDElem) ;
    }
}