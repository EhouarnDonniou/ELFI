#include "../include/headerTP5.h"

void CalSol(int NbLign, float** coord, float* UEX){
    for(int I=0; I<NbLign;I++){
        UEX[I] = solex(coord[I]);
    }
}