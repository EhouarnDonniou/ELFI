#include "../include/headerTP5.h"

/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 29/03/2026
--------------------------------------------------------------------------------
*/

void CalSol(int NbLign, float** coord, float* UEX){
    for(int I=0; I<NbLign;I++){
        UEX[I] = solex(coord[I]);
    }
}