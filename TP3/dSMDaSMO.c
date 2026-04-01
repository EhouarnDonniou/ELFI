/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 01/04/2026
--------------------------------------------------------------------------------
*/

#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"
#include "include/forfun.h"

void dSMDaSMO(int Nblign ,float* SecMembre ,int* NumDLDir ,float* ValDLDir ,int* AdPrCoefLi ,float*  Matrice ,int* Numcol ,int* AdSuccLi ,float* SecMemb0 ,int* AdPrCoLi0 ,float* Matrice0 ,int* NumCol0){
    cdesse_(&Nblign, AdPrCoefLi, numcol, AdSuccLi, Matrice, SecMembre, NumDLDir, ValDLDir, AdPrCoLi0, NumCol0, Matrice0, SecMemb0);
    affsmo_(&Nblign, AdPrCoLi0, NumCol0, Matrice0, SecMemb0);
}