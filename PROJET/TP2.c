/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 04/03/2026
--------------------------------------------------------------------------------
*/


//  Mettre le fichier de maillage à tester dans le dossier principal (3 exemples dans le dossier input)
//  Renommer ficmai avec le nom de ce fichier ainsi déposé
//  Compiler/Executer : bash compil.sh dans le dossier actuel
//  Les fichiers de résultats pour comparaisons sont dans le dossier output 
//   - (seulement 2 fichiers de résultats sont donnés)

/* Contenus des fichiers *.c
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

    //Allocation des variables et tableaux relatifs au maillage
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
    //Lecture des fichiers de maillage et de 
    int check = lecfima(ficmai,&typeEl,&nbtng,&coord,&nbtel,&ngnel,&nbneel,&nbaret,&nRefAr);
    lecNumRef(ficRef,&nRefDom,&nbRefD0,&nbRefD1,&nbRefF1,&numRefD0,&numRefD1,&numRefF1);

    //Allocation des variables et tableaux relatifs à un élément du maillage
    float** MatElem=alloctab(nbneel,nbneel);
    float* SMbrElem=malloc(nbneel*sizeof(float));
    int* NuDElem=malloc(nbneel*sizeof(int));
    float* uDElem=malloc(nbneel*sizeof(float));
    float** coorEl=alloctab(nbneel,2);

    //Boucle sur les éléments K
    for(int k=0;k<nbtel;k++){
        //Initialisation à 0 de MatElem, SMbrElem, NuDElem et uDElem
        for(int i=0; i<nbneel ; i++){
            SMbrElem[i]=0;
            NuDElem[i]=1;
            uDElem[i]=0;
            for(int j=0; j<nbneel; j++){
            MatElem[i][j]=0;
            }
        }
        
        //Selection des coordonnée des points de l'élément actuel K 
        // parmis l'ensemeble des coordonnées du maillage
        selectPts(nbneel,ngnel[k],coord,coorEl);

        //Calculs et mise ene forme du système linéaire pour l'élément actuel K
        cal1Elem(nRefDom, nbRefD0, numRefD0, nbRefD1, numRefD1, nbRefF1, numRefF1, 
                   typeEl, nbneel, coorEl, nbaret, nRefAr[k],
                   MatElem, SMbrElem, NuDElem, uDElem);
        
        //Affichage dans le terminal du syst.lin. associé à l'élément K et conditions de Dirichlet 
        impCalEl(k+1, typeEl, nbneel, MatElem, SMbrElem, NuDElem, uDElem) ;
    }

    //Libération de la mémoire
    free(numRefD0); free(numRefD1); free(numRefF1);
    free(NuDElem); free(uDElem);
    freetab(coord); freetab(ngnel); freetab(nRefAr);
    freetab(MatElem); free(SMbrElem); 
    
    free(coorEl);//free simple parce que ça pointe sur un espace mémoire aussi pointé par coord
                 //donc si coord est entièrement free, les espaces mémoires sont déjà libres 
}