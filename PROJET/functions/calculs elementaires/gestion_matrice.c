/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 11/02/2026
--------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include "../../include/headerTP2a.h"

//calcule la matrice Jacobienne de FK(x_hat) pour K actuel en un point x_hat donné (x_hat dans K_hat)
//utilise la formule pour x_hat noté x : 
//                  
//              (dFK/dx_j)(x) = Somme(l = 1:5-t)[aK_l * (dw_l/dx_j)(x)] , dans R^2
//
//on a donc (JFK(x))_i,j = (dFK_i/dx_j)(x) pour i,j = 1,2
//
//in : t, le type de l'élément associé au calcul.
//     pointeur aK[], liste des points d'interpo. géom de l'élément K actuel.
//     pointeur double derW, liste de valeurs des dw/dxi(x_hat) pour x_hat actuel.
//     pointeur double Jac, en entrée initialisée à 1 partout à l'avance.
//out : pointeur double Jac, matrice jacobienne de FK(x_hat) pour t==2,3.
//                           vecteur (dFK/dx_1, dFK/dx_2)(x_hat) pour t==1. 
void matJacob(int t, float* aK[], float** derW, float** Jac){

    int stop = 5 - t; 
    //condition d'arrêt : stop = 5-t = #points d'interpolation de chaque élément
    //  -> quadrangles  : stop = 5-1 = 4 
    //  -> triangles    : stop = 5-2 = 3
    //  -> segments     : stop = 5-3 = 2

    
    if(t==3){ //segments
        //à recheck, jsuis pas du tout sûr de la syntaxe
        for(int i=0; i<stop; i++){
            Jac[0] += derW[i]*aK[0];
            Jac[1] += derW[i]*aK[1];
        }
    }
    else{ //triangle et quadrangles
        for(int i=0; i<stop; i++){
            Jac[0][0] += derW[i][0]*aK[i][0];
            Jac[0][1] += derW[i][0]*aK[i][1];
            Jac[1][0] += derW[i][1]*aK[i][0];
            Jac[1][1] += derW[i][1]*aK[i][1];
        }
    }
}

//calcule le déterminant d'une matrice 2x2.
//inverse la matrice et retourne le déterminant.
//
//in : pointeur de matrice Mat pointant la matrice float 2x2 à inverser
//     pointeur de matrice Mat_inv 2x2 float qui acceuillera l'inverse de Mat
//out : float determinant, déterminant de Mat 
//
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