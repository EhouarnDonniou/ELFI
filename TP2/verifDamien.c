#include "include/headers.h"

void main(){
    float det, **A, **Ainv;
    A=alloctab(2,2);
    Ainv=alloctab(2,2);
    A[0][0]=1;
    A[0][1]=0.99999;
    A[1][0]=1;
    A[1][1]=1;
    det = invertM2x2(A,Ainv);
    printtab(A,2,2);
    printtab(Ainv,2,2);
    //Multiplication Matrice
    float **C=alloctab(2,2);
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            C[i][j]=0;
        }
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                C[i][j]+= A[i][k]*Ainv[k][j];
            }
        }
    }
    printtab(C,2,2);
}