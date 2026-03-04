/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 01/02/2026
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../include/headerTP2a.h"


//in : coordonnées du point x
//     valeurs des fonctions de base (calculées au préalable)
//     p le nombre de fonctions de base
//out : F_K(x) float* de dim 1x2 -> à entrer en argument avec les valeurs (0,0) et pas (x1,x2)
void transFK(float** pcoord_a, float* pvalfbase, float* fk_x, int p){
    for(int i=0; i<p; i++){
        fk_x[0] += pvalfbase[i] * pcoord_a[i][0];
        fk_x[1] += pvalfbase[i] * pcoord_a[i][1];
    }
}