#include "../include/headerTP1.h"
#include "../include/headerTP2a.h"
#include "../include/headerTP2b.h"
#include "../include/headerTP5.h"
#include "../include/utilitaires.h"
#include "../include/forfun.h"

//pas fini
//objectif : obtenir la longueur du tableau qui stockera la matrice profil à partir de la SMO
int dSMOaLongPR_nous(int NbLign, int* AdPrCoefLi0, int* NumCol0, float* Matrice0){
    int LongProfil = NbLign+1;
    for(int i=0; ;i++){
        LongProfil+=;
    }
    return LongProfil;
}


/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 8/04/2026
--------------------------------------------------------------------------------
*/

/*
    Passe du stockage SMO au stockage Profil pour la Matrice

    Arguments:
        AdPrcoefLi: FirstAdLi, Position dans Lmat du premier element stocke dans la ligne
        Matrice: Matrice avec le stockage SMO, Matrice = [Diag, Lmat]
        NumCol: ColInd, indice colonne de l'element i (Numcol[i]) dans LMat
        Profil: Postion du premier element d'une ligne dans MatProf, seulement compte dans la partie LmatProf
        MatProf: Stockage de la Matrice dans un vecteur qui est la matrice en stockage Profil, MatProf = [Diag,LmatProf]

*/
//void dSMOaPR(int* AdPrCoefLi,float* Matrice,int* NumCol,int* Profil,float* MatProf){
    
//}

/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 22/04/2026
--------------------------------------------------------------------------------
*/

/*
    Affiche la partie inférieur d'une matrice en stockage profil.
*/
void affSProf(int NbLign, int* Profil, float* MatProf){
    printf("\n");
        for(int i=0;i<NbLign;i++){
            printf("Ligne %d --", i+1);
            int CoefSurLigne = Profil[i]-Profil[i+1];
            for(int j=0;j<i-CoefSurLigne;j++){
                printf("%10.4e ",0.);
            }
            for(int j=0; j<CoefSurLigne; j++){
                printf("%10.4e ", MatProf[(NbLign-1)+Profil[i]+j]);
            }
            printf("%10.4e \n", MatProf[i]);
        }
}