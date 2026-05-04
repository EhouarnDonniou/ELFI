#include "../include/headerTP1.h"
#include "../include/headerTP2a.h"
#include "../include/headerTP2b.h"
#include "../include/headerTP5.h"
#include "../include/utilitaires.h"
#include "../include/forfun.h"

/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 8/04/2026
--------------------------------------------------------------------------------
*/

/*
    Retourne la longueur effective du vecteur stockant la matrice en Profil
    A partir stockage SMO de la même matrice
    Arguments:
        NbLign: Nombre de lignes dans la matrice
        AdPrcoefLi: FirstAdLi, Position dans Lmat du premier element stocke dans la ligne
        Matrice: Matrice avec le stockage SMO, Matrice = [Diag, LMat]
        NumCol: ColInd, indice colonne de l'element i (Numcol[i]) dans LMat

*/
int dSMOaLongPR_nous(int NbLign, int* AdPrCoLi0, int* NumCol0, float* Matrice0){
    int LongProfil = NbLign;
    for(int i=0; i<NbLign-1;i++){
        if(AdPrCoLi0[i]!=AdPrCoLi0[i+1]){
            LongProfil += (i+2)-NumCol0[AdPrCoLi0[i]-1];
        }
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
void dSMOaPR_nous(int NbLign, int* AdPrCoefLi,int* NumCol,float* Matrice,int LongProfil,int* Profil,float* MatProf){
    //init tout à 0, on aura pas à les "remplir" mais juste à les écraser là où ya des valeurs n-nulles
    for(int i=0;i<LongProfil;i++){
        MatProf[i]=0.;
    }
    int count = 0;

    //la matrice est diagonale 
    if(LongProfil==NbLign){
        for(int i=0;i<LongProfil;i++){
            MatProf[i]=Matrice[i];
            Profil[i]=1;
        }
        Profil[LongProfil]=0;
    }

    //pas que diagonale
    else{
        //Diagonale
 
        for(int i=0;i<NbLign;i++){
           Profil[i]=count+1;
            if(AdPrCoefLi[i]!=AdPrCoefLi[i+1]){
                
                for(int j=AdPrCoefLi[i]; j<AdPrCoefLi[i+1]; j++){
                    MatProf[NbLign+count+1+NumCol[j]-NumCol[AdPrCoefLi[i]]] = Matrice[NbLign+j];
                }
                
                count += 1+i-NumCol[AdPrCoefLi[i]];
            }
            
            MatProf[i]=Matrice[i];
            
        } 
        Profil[NbLign]=0;
        
    }
}

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
        printf("Ligne %d  ", 1);
        printf("%10.4e \n", MatProf[0]);

        for(int i=1;i<NbLign;i++){
            printf("Ligne %d  ", i+1);
            int CoefSurLigne = Profil[i]-Profil[i-1];

            for(int j=0; j<i; j++){

                printf("%10.4e, %d ", MatProf[NbLign+Profil[i]+j],Profil[i]);
            }

            printf("%10.4e \n", MatProf[i]);
        }

}