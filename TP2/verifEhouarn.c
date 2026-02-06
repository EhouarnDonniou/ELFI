#include "include/headers.h"

void main(){
    int t = 1;
    //chaques sommets de K_ref 
    float* x_ref_q = malloc(2*sizeof(float));
    float* valeurs = malloc(4*sizeof(float));

    //sommet local 1
    x_ref_q[0] = 0.5; x_ref_q[1] = 0.5;
    printf("x-ref 1 : \n");
    printtab(&x_ref_q, 1, 2);
    calFbase(t,x_ref_q,valeurs);
    printf("wi(x-ref) 1 : \n");
    printtab(&valeurs, 1, 4);

    // t = 2;

    // t = 3;
}