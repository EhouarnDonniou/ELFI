#include "include/headers.h"

void main(){
    int t = 1;
    //chaques sommets de K_ref 
    float* x_ref_q = malloc(2*sizeof(float));
    float* valeurs = malloc(4*sizeof(float));

    //sommet local 1
    x_ref_q[0] = 1; x_ref_q[1] = 0;
    printf("x-ref 1 : \n");
    calFbase(t,x,valeurs);
    printf("wi(x-ref) 1 : \n");
    

    //sommet local 2
    x_ref_q[0] = 1; x_ref_q[1] = 1;
    printf("x-ref 2 : \n");
    calFbase(t,x,valeurs);
    printf("wi(x-ref) 2 : \n");

    //sommet local 3
    x_ref_q[0] = 0; x_ref_q[1] = 1;
    printf("x-ref 3 : \n");
    calFbase(t,x,valeurs);
    printf("wi(x-ref) 3 : \n");

    //sommet local 4
    x_ref_q[0] = 0; x_ref_q[0] = 0;
    printf("x-ref 4 : \n");
    calFbase(t,x,valeurs);
    printf("wi(x-ref) 4 : \n");


    // t = 2;

    // t = 3;
}