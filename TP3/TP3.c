/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 04/03/2026
--------------------------------------------------------------------------------
*/


//pour compiler : bash compil.sh dans le dossier actuel

#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/headerTP3_4.h"
#include "include/forfun.h"
#include "include/utilitaires.h"

void main(){
    //déclaration-init pour la lecture de fichiers
    char* ficmai = "car3x3t_3";
    char* ficRef = "NUMREF.Test";

    //déclaration des variables géométriques
    float** coord;
    int** ngnel; 
    int typeEl, nbtng, nbtel, nbneel, nbaret;

    //déclaration des variables relatives aux conditions de bord
    int** nRefAr;
    int nRefDom, nbRefD0, nbRefD1, nbRefF1;
    int* numRefD0;
    int* numRefD1;
    int* numRefF1;

    //appel des fonctions de lecture de fichiers pour initialiser les variables associées au maillage/domaine
    int check = lecfima(ficmai,&typeEl,&nbtng,&coord,&nbtel,&ngnel,&nbneel,&nbaret,&nRefAr);
    lecNumRef(ficRef,&nRefDom,&nbRefD0,&nbRefD1,&nbRefF1,&numRefD0,&numRefD1,&numRefF1);

    //declaration des variables relatives au stockage morse désordonné

    float* SecMembre = malloc(nbtng*sizeof(float));
    int* NumDLDir = malloc(nbtng*sizeof(int));
    float* ValDLDir = malloc(nbtng*sizeof(int));
    int* AdPrCoefLi = calloc(nbtng,sizeof(int)); int NbCoef = AdPrCoefLi[nbtng]-1;
    float* Matrice = malloc(nbtng+NbCoef*sizeof(float));
    int* NumCol = malloc(NbCoef*sizeof(int));
    int* AdSuccLi = malloc(NbCoef*sizeof(int));
 
    Assemblage(coord ,ngnel ,nRefAr ,typeEl ,nbtng ,nbtel ,nbneel ,nbaret ,
               nbtng ,SecMembre ,NumDLDir ,ValDLDir ,AdPrCoefLi ,Matrice ,NumCol ,AdSuccLi);

//affichage système assemblé

    affsmd_(&nbtng, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, NumDLDir, ValDLDir);


//quitter

    free(numRefD0); free(numRefD1); free(numRefF1);
    freetab(coord); freetab(ngnel); freetab(nRefAr);

    free(SecMembre); free(Matrice); 
    free(NumDLDir); free(ValDLDir);
    free(AdPrCoefLi); free(AdSuccLi); free(NumCol); 
    
}