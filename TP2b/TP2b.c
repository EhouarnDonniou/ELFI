/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 04/03/2026
--------------------------------------------------------------------------------
*/
#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"

void main(){
    char* ficmai = "car3x3t_3";
    char* ficRef = "NUMREF.Test";
    float** coord;
    int** ngnel; 
    int** nRefAr;
    int typeEl, nbtng, nbtel, nbneel, nbaret;
    int nRefDom, nbRefD0, nbRefD1, nbRefF1;
    int* numRefD0;
    int* numRefD1;
    int* numRefF1;
    int  check = lecfima(ficmai,&typeEl,&nbtng,&coord,&nbtel,&ngnel,&nbneel,&nbaret,&nRefAr);
    lecNumRef(ficRef,&nRefDom,&nbRefD0,&nbRefD1,&nbRefF1,&numRefD0,&numRefD1,&numRefF1);

    //Allocation
    float** MatElem=alloctab(nbneel,nbneel);
    float* SMbrElem=malloc(nbneel*sizeof(float));
    int* NuDElem=malloc(nbneel*sizeof(int));
    float* uDElem=malloc(nbneel*sizeof(float));
    float** coorEl=alloctab(nbneel,2);

    //Boucle sur les éléments K
    for(int k=0;k<nbtel;k++){
        printf("\n \n ---------Element actuel K = %d \n", k+1);
        //Initialisation à 0 de MatElem, SMbrElem, NuDElem et uDElem
        for(int i=0; i<nbneel ; i++){
            SMbrElem[i]=0;
            NuDElem[i]=1;
            uDElem[i]=0;
            for(int j=0; j<nbneel; j++){
            MatElem[i][j]=0;
            }
        }
        
        selectPts(nbneel,ngnel[k],coord,coorEl);

        cal1Elem(nRefDom, nbRefD0, numRefD0, nbRefD1, numRefD1, nbRefF1, numRefF1, 
                   typeEl, nbneel, coorEl, nbaret, nRefAr[k],
                   MatElem, SMbrElem, NuDElem, uDElem);

        impCalEl(k+1, typeEl, nbneel, MatElem, SMbrElem, NuDElem, uDElem) ;
    }
}