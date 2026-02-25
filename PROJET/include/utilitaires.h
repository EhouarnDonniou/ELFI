/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 11/02/2026
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

//gestion des tableaux à 2 dimensions
float** alloctab(int, int);
int** alloctabint(int, int);
void freetab(void*);
void printtab(float**, int, int);
void SommeMat(float**, float**, float**, int, int);
void ProduitMat(float**, float**, float**, int ,int ,int ,int);