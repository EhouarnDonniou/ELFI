#include "include/headers.h"

void main(){
    float **A=alloctab(2,2);
    float **Ainv=alloctab(2,2);
    A[0][0]=1;
    A[0][1]=1;
    A[1][0]=1;
    A[1][1]=1;
    printtab(A,2,2);
}