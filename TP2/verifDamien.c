#include "include/headers.h"

void main(){
    float det, **A, **Ainv;
    A=alloctab(2,2);
    Ainv=alloctab(2,2);
    A[0][0]=1;
    A[0][1]=1;
    A[1][0]=1;
    A[1][1]=1;
    det = invertM2x2(A,Ainv);
    printtab(A,2,2);
    printtab(Ainv,2,2);
}