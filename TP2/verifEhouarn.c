#include "include/headers.h"

void main(){
    int t = 1;
    //chaques sommets de K_ref (dim1 : i ; dim2 : j)
    float** x_ref_q = alloctab(2, 1);
    //sommet local 1
    *x_ref_q[0] = 1; *x_ref_q[1] = 0;
    printf("x-ref 1 : \n");
    printtab(x_ref_q,2,1);
    printf("%f %f", *x_ref_q[0] , *x_ref_q[1]);


    //sommet local 2
    *x_ref_q[0] = 1; *x_ref_q[1] = 1;
    printf("x-ref 2 : \n");
    printtab(x_ref_q,2,1);

    //sommet local 3
    *x_ref_q[0] = 0; *x_ref_q[1] = 1;
    printf("x-ref 3 : \n");
    printtab(x_ref_q,2,1);

    //sommet local 4
    *x_ref_q[0] = 1; *x_ref_q[0] = 1;
    printf("x-ref 4 : \n");
    printtab(x_ref_q,2,1);


    // t = 2;

    // t = 3;
}