#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int dSMOaLongPR_nous(int NbLign, int* AdPrCoefLi0, int* NumCol0, float* Matrice0);

void dSMOaPR_nous(int NbLing, int* AdPrCoefLi,int* NumCol,float* Matrice,int LongProfilMat,int* Profil,float* MatProf);

void affSProf(int NbLign, int* Profil, float* MatProf);