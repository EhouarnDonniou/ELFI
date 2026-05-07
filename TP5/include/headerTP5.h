#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int dSMOaLongPR(int, int*, int*, float*);
void dSMOaPR(int, int*,int*,float*,int,int*,float*);

float solex(float* coor);
void CalSol(int NbLign, float** coord, float* UEX);