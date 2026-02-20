/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI 

    Ecrit le 20/02/2026
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>


//fonctions de définition du problème 
//intérieur
float A11(float* ); 
float A22(float* );
float A12(float* );
float A00(float* );
//en GammaN
float BN(float* );
//second membre intérieur
float FOMEGA(float* );
//second membre en GammeN
float FN(float* );
//en GammaD (Dirichlet)
float UD(float* );