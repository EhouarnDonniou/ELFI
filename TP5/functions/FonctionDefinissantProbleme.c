#include "../include/headerTP2b.h"

/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 06/05/2026
--------------------------------------------------------------------------------
*/

extern int nucas; //numéro de cas (1,2,3)
extern float xmin; extern float xmax;
extern float ymin; extern float ymax;

/*
Contient les fonctions : 
    -A11, A12, A22
    -A00, BN
    -FOMEGA, FN
    -UD 
*/
// un point de coordonnées x=(x1,x2)

float A11(float *x){
    return 1.0;
}

float A22(float *x){
    return 1.0;
}

float A12(float *x){
    return 0.0;
}

float A00(float *x){
    float val = 0.0;
    switch (nucas) {
        case 1 :
	        val=0.0;
	        break;
        case 2 :
	        val=0.0;
	        break;
        case 3 :
	        val=1.0;
	        break;
        default :
	        printf("*** A00 : exemple non prevu.\n");
	        break;
    }
  return(val);
}

float BN(float *x){
    return 0.0;
}

float FOMEGA(float* x){
    const float PI = M_PI;
    float val = 0.;
    switch (nucas) {
        case 1 :
	        val=-32.0*(x[1]*(1-x[1])+x[0]*(1-x[0]));
	        break;
        case 2 :
	        val= (2.0*PI*PI)*sin(PI*x[0])*sin(PI*x[1]);
	        break;
        case 3 :
	        val=(2.0*PI*PI+1.0)*cos(PI*x[0])*cos(PI*x[1]);
	        break;
        default :
	        printf("*** FOMEGA : exemple non prevu.\n");
	        break;
  }
  return(val);
}

float FN(float *x){
    const float PI = M_PI;
    float Tol = 1.0e-6;

    //détermine les composantes du vecteur normal en fonction des min/max du domaine.
    float norm_x= 0.0 + -1.0*(fabs(x[0]-xmin)<Tol) + 1.0*(fabs(x[0]-xmax)<Tol);
    float norm_y= 0.0 + -1.0*(fabs(x[1]-ymin)<Tol) + 1.0*(fabs(x[1]-ymax)<Tol);

    float val = 0.0;
    switch (nucas) {
        case 1 :
            val = norm_x*(16.0*(2*x[0]*x[1]-2*x[0]*x[1]*x[1]+x[1]*x[1]-x[1])) + norm_y*(16.0*(2*x[0]*x[1]-2*x[0]*x[0]*x[1]+x[0]*x[0]-x[0]));
            break;
        case 2 :
	        val = norm_x*(-PI*cos(PI*x[0])*sin(PI*x[1])) + norm_y*(-PI*sin(PI*x[0])*cos(PI*x[1]));
	        break;
        case 3 :
	        val = norm_y*(-PI*cos(PI*x[0])*sin(PI*x[1])) + norm_x*(-PI*sin(PI*x[0])*cos(PI*x[1]));
	        break;
        default :
	        printf("*** FN : exemple non prevu.\n");
	        break;
    }
  return(val);
}

float UD(float *x){
    const float PI = M_PI;
    float val = 0.0;

    switch (nucas) {
        case 1 :
	        val=16.0*x[0]*x[1]*(x[0]-1)*(1-x[1]);
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
