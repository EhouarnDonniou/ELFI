/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 18/02/2026
--------------------------------------------------------------------------------
*/

#include "../PROJET/include/utilitaires.h"
void main(){
    int l,m,k;
    l=8;
    m=3;
    k=3;
    float **A=alloctab(l,m);
    //Coeff A
    for(int i=0;i<l;i++){
        for(int j=0;j<m;j++){
            A[i][j]= i+j;
        }
    }
    float **B=alloctab(l,m);
    //Coeff B
    for(int i=0;i<l;i++){
        for(int j=0;j<m;j++){
            B[i][j]= j-i;
        }
    }
    float **C=alloctab(l,m);

    float **D=alloctab(k,l);
    //Coeff D
    for(int i=0;i<k;i++){
        for(int j=0;j<l;j++){
            D[i][j]= i*j;
        }
    }
    float **E=alloctab(k,m);

    //Somme A+B=C
    SommeMat(A,B,C,l,m);
    printf("A:\n");
    printtab(A,l,m);
    printf("B:\n");
    printtab(B,l,m);
    printf("A+B:\n");
    printtab(C,l,m);
    //Multiplication A*D=E
    ProduitMat(A,D,E,l,m,k,l);
    printf("A:\n");
    printtab(A,l,m);
    printf("D:\n");
    printtab(D,k,l);
    printf("AD:\n");
    printtab(E,k,m);

}