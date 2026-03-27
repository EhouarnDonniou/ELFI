/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 04/03/2026
--------------------------------------------------------------------------------
*/


//pour compiler : bash compil.sh dans le dossier actuel

/* Contenus des fichiers .c
CalSysLin1Elem.c : 
    -Cal1Elem
    -intElem, intAret 
    -numNaret, selectPts

CalQuadrature.c : 
    -W, WW, ADWDW 
    -transFk, calFbase, calDerFbase
    -valq, ppquad
    -matJacob, invertM2x2

FonctionDefinissantProbleme.c : 
    -A11, A12, A22
    -A00, BN
    -FOMEGA, FN
    -UD 

EcritLectMaillage.c : 
    -lecfima
    -lecNumref 

    -lecture_fichier_maillage
    -nombre_points, coordonees_points
    -ecriture_mtpq, etiqAr, calc_s_ecrire_s_et_r

gestion_tab.c
    -alloctab, freetab
    -alloctabint 
    -printtab
    -SommeMat, ProduitMat

impcalel.c : impcalel
*/

#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"

void main(){
    char* ficmai = "car1x1q_4";
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

        impCalEl(k+1, typeEl, nbneel, MatElem, SMbrElem, NuDElem, uDElem) ;
    }

    free(numRefD0); free(numRefD1); free(numRefF1);
    free(NuDElem); free(uDElem);
    freetab(coord); freetab(ngnel); freetab(nRefAr);
    freetab(MatElem); free(SMbrElem); 
    
    free(coorEl);//free simple parce que ça pointe sur un espace mémoire aussi pointé par coord
                 //donc si coord est entièrement free, les espaces mémoires sont déjà libres 
}