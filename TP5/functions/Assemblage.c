/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 25/03/2026
--------------------------------------------------------------------------------
*/

#include "../include/headerTP1.h"
#include "../include/headerTP2a.h"
#include "../include/headerTP2b.h"
#include "../include/utilitaires.h"
#include "../include/forfun.h"

void Assemblage(int nRefDom, int nbRefD0, int* numRefD0, int nbRefD1, int* numRefD1, int nbRefF1, int* numRefF1, float** coord ,int** ngnel ,int** nRefAr ,int typeEl ,int nbtng ,int nbtel ,int nbneel ,int nbaret ,int Nblign ,int NbCoef, float* SecMembre ,int* NumDLDir ,float* ValDLDir ,int* AdPrCoefLi ,float*  Matrice ,int* NumCol ,int* AdSuccLi,float* SecMemb0 ,int* AdPrCoLi0 ,float* Matrice0 ,int* NumCol0){
    
    //initialisation des variables allouées précédement
    int NextAd=1;
    for(int i=0; i<Nblign; i++){
        SecMembre[i]=0;  SecMemb0[i]=0;
        Matrice[i]=0;    Matrice0[i]=0;
        AdPrCoefLi[i]=0; AdPrCoLi0[i]=0;
        ValDLDir[i]=0;   NumDLDir[i]=i+1; 
    }
    for(int i=0; i<NbCoef; i++){
        Matrice[Nblign+i]=0; 
        Matrice0[Nblign+i]=0;
        NumCol[i]=0;
        AdSuccLi[i]=0;
    }
    
    //Allocation des variables locales
    float** MatElem=alloctab(nbneel,nbneel);
    float* SMbrElem=malloc(nbneel*sizeof(float));
    int* NuDElem=malloc(nbneel*sizeof(int));
    float* uDElem=malloc(nbneel*sizeof(float));
    float** coorEl=alloctab(nbneel,2);


    //Boucle sur les éléments K
    for(int k=0;k<nbtel;k++){
        
        //Initialisation à 0 de MatElem, SMbrElem, NuDElem et uDElem
        for(int i=0;i<nbneel;i++){
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

        //impCalEl(k+1, typeEl, nbneel, MatElem, SMbrElem, NuDElem, uDElem) ; //enfait on impcalel (c'est dans les fichiers de test)

        /* /!\ i et j commencent à 1 et k à 0 /!\ */
        for(int i=1;i<=nbneel;i++){
            int I=ngnel[k][i-1]; // I = gK(i) (i est local, I est global)

            for(int j=1; j<i;j++){
                int J=ngnel[k][j-1]; // J = gK(j) (j est local, J est global)

                int Jtild = (((I) < (J)) ? (I) : (J)) ;
                int Itild = (((I) > (J)) ? (I) : (J)) ;

                assmat_(&Itild, &Jtild, &MatElem[i-1][j-1], AdPrCoefLi, NumCol, AdSuccLi, &Matrice[Nblign], &NextAd); 
            }
            Matrice[I-1] += MatElem[i-1][i-1];
            SecMembre[I-1] += SMbrElem[i-1]; 

            

            if(NuDElem[i-1]==-1){
                NumDLDir[I-1] = -I; 
                ValDLDir[I-1] = uDElem[i-1];
            }
            if(NuDElem[i-1]==0){
                NumDLDir[I-1] = 0; 
            }
        }
    }
    AdPrCoefLi[Nblign-1] = NextAd;

    cdesse_(&nbtng, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, NumDLDir, ValDLDir, AdPrCoLi0, NumCol0, Matrice0, SecMemb0);

    //Libération
    freetab(MatElem); free(SMbrElem);
    free(NuDElem); free(uDElem);
    free(coorEl); // attention à pas le freetab !
}