/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 01/02/2026
--------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include "../include/headers.h"


//calcule le déterminant d'une matrice 2x2
//inverse la matrice et retourne le déterminant
//
//in : pointeur de matrice Mat pointant la matrice float 2x2 à inverser
//     pointeur de matrice Mat_inv 2x2 float qui acceuillera l'inverse de Mat
//out : float determiant, déterminant de Mat 
// edge case : 
//      det(Mat)=0 => determinant = 0 et mat n'est pas inversée (Mat_inverse non-modifiée)
float invertM2x2(float*** Mat, float*** Mat_inv){
    float determiant = (*Mat)[0][0]*(*Mat)[1][1] - (*Mat)[0][1]*(*Mat)[1][0];
    if(determinant<= 10e-16 ){
        printf("/! ERROR \n La matrice n'est pas inversible!");
        return 0;
    }

    (*Mat_inverse)[0][0] = (*Mat)[1][1]/determinant;
    (*Mat_inverse)[1][1] = (*Mat)[0][0]/determinant;
    (*Mat_inverse)[0][1] = -(*Mat)[0][1]/determinant;
    (*Mat_inverse)[1][0] = -(*Mat)[1][0]/determinant;

    return(determinant);
}