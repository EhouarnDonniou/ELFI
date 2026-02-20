/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 11/02/2026
--------------------------------------------------------------------------------
*/
// un point de coordonnées x=(x1,x2)

#include "../include/headerTP2b.h"

float A11(float *x){
    return 1;
}

float A22(float *x){
    return 1;
}

float A12(float *x){
    return 0;
}

float A00(float *x){
    return 1;
}

float BN(float *x){
    return 0;
}

float FOMEGA(float *x){
    return 1;
}

float FN(float *x){
    return 1;
}

float UD(float *x){
    return 100*x[0]+x[1];
}
