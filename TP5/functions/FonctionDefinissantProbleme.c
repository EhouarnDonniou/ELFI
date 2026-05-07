#include "../include/headerTP2b.h"

extern int nucas; //numéro de cas (1,2,3)

/*
Contient les fonctions : 
    -A11, A12, A22
    -A00, BN
    -FOMEGA, FN
    -UD 
*/
// un point de coordonnées x=(x1,x2)

float A11(float *x){
    return 1.;
}

float A22(float *x){
    return 1.;
}

float A12(float *x){
    return 0.;
}

float A00(float *x){
    float val = 0.;

    switch (nucas) {
        case 1 :
	    val=0.;
	    break;
        case 2 :
	    val=0.;
	    break;
        case 3 :
	    val=1.;
	    break;
        default :
	    printf("*** A00 : exemple non prevu.\n");
	    break;
    }
  return(val);
}

float BN(float *x){
    return 0.;
}

float FOMEGA(float* x){
    const float PI = M_PI;
    float val = 0.;
    switch (nucas) {
        case 1 :
	        val=32.0*(x[1]*(1-x[1])+x[0]*(1-x[0]));
	        break;
        case 2 :
	        val=2.*PI*PI*sin(PI*x[0])*sin(PI*x[1]);
	        break;
        case 3 :
	        val=(1.-2.*PI*PI)*cos(PI*x[0])*cos(PI*x[1]);
	        break;
        default :
	        printf("*** FOMEGA : exemple non prevu.\n");
	        break;
  }
  return(val);
}

float FN(float *x){
    const float PI = M_PI;
    float val = 0.;

    switch (nucas) {
        case 1 :
	    val=0.;
	    break;
        case 2 :
	    val=0.;
	    break;
        case 3 :
	    if(x[1]==0.){
            val=0.;
        }
        if(x[0]==0.){
            val=0.;
        }
        if(x[1]==1. || x[1]==1/3){
            val=-PI*cos(PI*x[0])*sin(PI*x[1]);
        }
        if(x[0]==1. || x[0]==1/3 ){
            val=-PI*sin(PI*x[0])*cos(PI*x[1]);
        }
	    break;
        default :
	    printf("*** FN : exemple non prevu.\n");
	    break;
    }
  return(val);
}

float UD(float *x){
    const float PI = M_PI;
    float val = 0.;

    switch (nucas) {
        case 1 :
	    val=16.*x[0]*x[1]*(x[0]-1)*(1-x[1]);
	    break;
        case 2 :
	    val=sin(PI*x[0])*sin(PI*x[1]);
	    break;
        case 3 :
	    val=cos(PI*x[0])*cos(PI*x[1]);
	    break;
        default :
	    printf("*** UD : exemple non prevu.\n");
	    break;
    }
  return(val);
}
