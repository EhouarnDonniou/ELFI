#include <stdio.h>
#include <stdlib.h>
#include "../include/headers.h"

//le vecteur float* valeurs a été calloc avant.
//c-a-d, tout est initialisé à 0 dès le début. 
void calFbase(int t, int* point, float** valeurs){
    switch(t){
        //quadrangles -> ordre 1 : Q1
        case(1):
            *valeur[0] = point[0]-point[0]*point[1];
            *valeur[1] = point[0]*point[1];
            *valeur[2] = point[1]-point[0]*point[1];
            *valeur[3] = 1 - point[1]-point[0] + point[0]*point[1];
        //triangles -> ordre 1 : P1
        case(2):
            *valeur[0] = point[0];
            *valeur[1] = point[1];
            *valeur[2] = 1-point[0]-point[1];
        //segments
        case(3):
            *valeur[0] = *point;
            *valeur[1] = -(*point)+1;
    }
}
