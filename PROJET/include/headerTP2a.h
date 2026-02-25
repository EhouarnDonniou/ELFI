/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI 

    Ecrit le 04/02/2026
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

/*
types : t==1 -> quadrangles
        t==2 -> triangles
        t==3 -> segments
*/

//association de la valeur q en fonction de t
int valq(int*);

//renvoie le vecteur poids et matrice des poits de quadrature en fonction de t
void ppquad(int , float* , float**);

//calcul des fonctions de base sur l'élément de référence 
//élément 1 - quadrangle
//------- 2 - triangle
//------- 3 - segment
void calFbase(int, float*, float*);
//calcul de dérivées des fonctions de base sur l'élément de référence
void calDerFbase(int, float*, float**);

//fonction de changement de variable 
//fait la transformation d'un élémént K à l'élémént de référence
void transFK(float**, float*, float*, int);

//calcule le déterminant d'une matrice 2x2
//inverse la matrice et retourne le déterminant
float invertM2x2(float**, float**);

//calcule et retourne la matrice Jacobienne
//ou le vecteur différentiel selon la dimension
void matJacob(int, float**, float**, float**);

//renvoie le couple de sommets pour (local) pour l'arête (locale) en entrée
//différentie les quadrangles des triangles
void numNaret(int*, int*, int);

void selectPts(int, int*, float**, float**);