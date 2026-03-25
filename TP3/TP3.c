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

    //declaration des variables relatives au stockage morse
    int NbLign = ?;
    float* SecMembre = malloc(NbLign*sizeof(float));
    int* NumDLDir = malloc(NbLign*sizeof(int));
    int* ValDLDir = malloc(NbLign*sizeof(int));
    int* AdPrCoefLi = malloc(NbLign*sizeof(int)); int NbCoef = AdPrCoefLi[NbLign]-1;
    float* Matrice = malloc(NbCoef*sizeof(float));
    int* NumCol = malloc(NbCoef*sizeof(int));
    int* AdSuccLi = malloc(NbCoef*sizeof(int));
 
    Assemblage(coord ,ngnel ,nRefAr ,typeEl ,nbtng ,nbtel ,nbneel ,nbaret ,
            Nblign ,SecMembre ,NumDLDir ,ValDLDir ,AdPrCoefLi , Matrice , Numcol , AdSuccLi);

//affichage système assemblé
/*
    affsmd(const int *nblign, const int *adprcl, const int *numcol,
           const int *adsucl, const float *matris, const float *secmbr,
           const int *nuddir, const float *valdir);
*/
    


//quitter

    free(numRefD0); free(numRefD1); free(numRefF1);
    freetab(coord); freetab(ngnel); freetab(nRefAr);
}