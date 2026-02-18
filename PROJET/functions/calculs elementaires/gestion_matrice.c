/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 11/02/2026
--------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include "../include/headerTP2a.h"


void matJacob(int d, float* aK[], float** derW, float** Jac){
    if(d==1){//segments
        //à recheck, jsuis pas du tout sûr de la syntaxe
        for(int i=0;i<2;i++){
            Jac[0] += derW[i]*aK[0];
            Jac[1] += derW[i]*aK[1];
        }
    }
    if(d==2){//triangles et quadrangles
        //ajouter un stop sur 3 ou 4 en fonction de la taille de l'élément?
        for(int i=0;i<4;i++){
            Jac[0][0] += derW[i][0]*aK[i][0];
            Jac[0][1] += derW[i][0]*aK[i][1];
            Jac[1][0] += derW[i][1]*aK[i][0];
            Jac[1][1] += derW[i][1]*aK[i][1];
        }
    }
}

//calcule le déterminant d'une matrice 2x2
//inverse la matrice et retourne le déterminant
//
//in : pointeur de matrice Mat pointant la matrice float 2x2 à inverser
//     pointeur de matrice Mat_inv 2x2 float qui acceuillera l'inverse de Mat
//out : float determinant, déterminant de Mat 
// edge case : 
//      det(Mat)=0 => determinant = 0 et mat n'est pas inversée (Mat_inverse non-modifiée)
float invertM2x2(float** Mat, float** Mat_inv){
    float determinant = Mat[0][0]*Mat[1][1] - Mat[0][1]*Mat[1][0];
    if(determinant<= 10e-6 ){
        printf("/! ERROR \n La matrice n'est pas inversible!\n");
        return 0;
    }

    Mat_inv[0][0] = Mat[1][1]/determinant;
    Mat_inv[1][1] = Mat[0][0]/determinant;
    Mat_inv[0][1] = -Mat[0][1]/determinant;
    Mat_inv[1][0] = -Mat[1][0]/determinant;

    return(determinant);
}