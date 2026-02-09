#include "include/headers.h"

void main(){
    int t = 1;
    printf(" QUADRANGLE X = (1/2,1/2) \n");
    float* x_ref_qt = malloc(2*sizeof(float));
    float* valeurs_qu = malloc(4*sizeof(float));
    float** der_qu = alloctab(4,2);

    x_ref_qt[0] = 0.5; x_ref_qt[1] = 0.5;
    //calFbase(t,x_ref_qt,valeurs_qu);
    // printf("x-ref int : \n");
    // printtab(&x_ref_qt, 1, 2);
    // printf("wi(x-ref) int : \n");
    // printtab(&valeurs_qu, 1, 4);
    calDerFbase(t,x_ref_qt,der_qu);
    printtab(der_qu, 4, 2);

    t = 2;
    printf(" TRIANGLE X = (1/4,1/4) \n");
    float* valeurs_tr = malloc(3*sizeof(float));
    float** der_tr = alloctab(3,2);

    x_ref_qt[0] = 1/4; x_ref_qt[1] = 1/4;
    calFbase(t,x_ref_qt,valeurs_tr);
    // printtab(&x_ref_qt, 1, 2);
    // printf("wi(x-ref) int : \n");
    // printtab(&valeurs_tr, 1, 3);
    calDerFbase(t,x_ref_qt,der_tr);
    printtab(der_tr, 3, 2);

    t = 3;
    printf(" SEGMENT X = 0 \n");
    float x_segment = 0.5;
    float* valeurs_seg = malloc(2*sizeof(float));
    float* der_seg = malloc(2*sizeof(float));

    calFbase(t,&x_segment,valeurs_seg);
    // printf("%f \n",x_segment);
    // printf("wi(x-ref) int : \n");
    // printtab(&valeurs_seg, 1, 2);
    calDerFbase(t,x_ref_qt,&der_seg);
    printtab(&der_seg, 1, 2);

    free(x_ref_qt);
    free(valeurs_qu);
    free(valeurs_tr);
    free(valeurs_seg);
    free(der_seg);
    freetab(der_tr);
    freetab(der_qu);

}