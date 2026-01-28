#include <stdio.h>
#include <stdlib.h>
#include "../include/headers.h"

//calcul de wi(x) 
void calFbase(int t, int* x, float** valeurs){
    switch(t){
        //quadrangles -> ordre 1 : Q1
        case(1):
            *valeur[0] = x[0]-x[0]*x[1];
            *valeur[1] = x[0]*x[1];
            *valeur[2] = x[1]-x[0]*x[1];
            *valeur[3] = 1 - x[1]-x[0] + x[0]*x[1];
        //triangles -> ordre 1 : P1
        case(2):
            *valeur[0] = x[0];
            *valeur[1] = x[1];
            *valeur[2] = 1-x[0]-x[1];
        //segments
        case(3):
            *valeur[0] = *x;
            *valeur[1] = -(*x)+1;
    }
}
