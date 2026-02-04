/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 04/02/2026
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/headers.h"

void numNaret(int* numaret, int numsommets[], int t){
    switch(*numaret){
        case(1):
            numsommets[0]=1;
            numsommets[1]=2;
            break;
        case(2):
            numsommets[0]=2;
            numsommets[1]=3;
            break;
        case(3):
            if(t==1){ //quadrangle
                numsommets[0]=3;
                numsommets[1]=4;
            }
            if(t==2){ //triangle
                numsommets[0]=3;
                numsommets[1]=1;
            }
            break;
        case(4): //uniquement pour le quadrangle
            numsommets[0]=4;
            numsommets[1]=1;
            break;
    }
}