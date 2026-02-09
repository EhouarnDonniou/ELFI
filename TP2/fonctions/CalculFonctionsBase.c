/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 28/01/2026
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/headers.h"

//calcul de wi(x) pour x dans K et wi fonction de base sur K
//les wi sont d'ordre 1 tq wi(sommet_j)=1 si j==i
//                                     =0 si j!=i 
void calFbase(int t, float* x, float* valeur){
    switch(t){
        //quadrangles -> ordre 1 : Q1
        case(1):
            valeur[0] = x[0]-x[0]*x[1];
            valeur[1] = x[0]*x[1];
            valeur[2] = x[1]-x[0]*x[1];
            valeur[3] = 1 - x[1]-x[0] + x[0]*x[1];
            break;
        //triangles -> ordre 1 : P1
        case(2):
            valeur[0] = x[0];
            valeur[1] = x[1];
            valeur[2] = 1-x[0]-x[1];
            break;
        //segments
        case(3):
            valeur[0] = *x;
            valeur[1] = -(*x)+1;
            break;
    }
}

//calcul de dwi/dxj(x) pour x dans K et wi fonction de base sur K
//pour K dans le plan, x = (x1,x2)
void calDerFbase(int t, float* x, float** valeur){
    switch(t){
        //quadrangles
        case(1):
            valeur[0][0] = 1-x[1]; 
            valeur[0][1] = -x[0];

            valeur[1][0] = x[1];
            valeur[1][1] = x[0];

            valeur[2][0] = -x[1];
            valeur[2][1] = 1-x[0];
            
            valeur[3][0] = -1 + x[1];
            valeur[3][1] = -1 + x[0];
            break;
        //triangles 
        case(2):
            valeur[0][0] = 1;
            valeur[0][1] = 0;

            valeur[1][0] = 0;
            valeur[1][1] = 1;

            valeur[2][0] = -1;
            valeur[2][1] = -1;
            break;
        //segments
        case(3):
            valeur[0][0] = 1;
            valeur[1][0] = -1;
            break;
    }
}
