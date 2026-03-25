/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 25/03/2026
--------------------------------------------------------------------------------
*/

#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"
#include "include/forfun.h"

void Assemblage(float** coord ,int** ngnel ,int** nRefAr ,int typeEl ,int nbtng ,int nbtel ,int nbneel ,int nbaret ,int Nblign ,float* SecMembre ,int* NumDLDir ,float* ValDLDir ,int* AdPrCoefLi ,float*  Matrice ,int* Numcol ,int* AdSuccLi){
    
    int NextAd=1;
    //Allocation
    float** MatElem=alloctab(nbneel,nbneel);
    float* SMbrElem=malloc(nbneel*sizeof(float));
    int* NuDElem=malloc(nbneel*sizeof(int));
    float* uDElem=malloc(nbneel*sizeof(float));
    float** coorEl=alloctab(nbneel,2);

    //Boucle sur les éléments K
    for(int k=0;k<nbtel;k++){
        //printf("\n \n ---------Element actuel K = %d \n", k+1);
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

        impCalEl(k+1, typeEl, nbneel, MatElem, SMbrElem, NuDElem, uDElem) ; //enfait on impcalel (c'est dans les fichiers de test)

        for(int i=1;i<Nblign+1;i++){
            int I=ngnel[k-1][i-1];
            
            for(int j=1; j<i;j++){
                int J=ngnel[k-1][j-1];
                Jtild = (((I) < (J)) ? (I) : (J)) ;
                Itild = (((I) > (J)) ? (I) : (J)) ;
                assmat(&Itild,&Jtild,); // A FINIR
            }
        }


        
    }


    free(numRefD0); free(numRefD1); free(numRefF1);
    free(NuDElem); free(uDElem);
}