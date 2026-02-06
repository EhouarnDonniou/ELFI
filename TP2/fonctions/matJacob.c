/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI 

    Ecrit le 04/02/2026
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/headers.h"

void matJacob(int d, float* aK[], float** derW, float** Jac){
    if(d==1){//segmentsç
        //à recheck, jsuis pas du tout sûr de la syntaxe
        for(int i=0;i<2;i++){
            Jac[0] += derW[i]*aK[0];
            Jac[1] += derW[i]*aK[1];
        }
    }
    if(d==2){//triangles et quadrangles
        //ajouter un stop sur 3 ou 4 en fonction de la taille de l'élément?
        for(int i=0;i<4;i++){
            Jac[0][0] += derW[i][0]*aK[i][0];
            Jac[0][1] += derW[i][0]*aK[i][1];
            Jac[1][0] += derW[i][1]*aK[i][0];
            Jac[1][1] += derW[i][1]*aK[i][1];
        }
    }
}