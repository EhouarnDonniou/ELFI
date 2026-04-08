/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 8/04/2026
--------------------------------------------------------------------------------
*/

#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"
#include "include/forfun.h"
/*
    Passe du stockage SMO au stockage Profil pour la Matrice

    Arguments:
        AdPrcoefLi: FirstAdLi, Position dans Lmat du premier element stocke dans la ligne
        Matrice: Matrice avec le stockage SMO, Matrice = [Diag, Lmat]
        NumCol: ColInd, indice colonne de l'element i (Numcol[i]) dans LMat
        Profil: Postion du premier element d'une ligne dans MatProf, seulement compte dans la partie LmatProf
        MatProf: Stockage de la Matrice dans un vecteur qui est la matrice en stockage Profil, MatProf = [Diag,LmatProf]

*/
void dSMOaPR(int* AdPrCoefLi,float* Matrice,int* NumCol,int* Profil,float* MatProf){
    
}