/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 18/02/2026
--------------------------------------------------------------------------------
*/

#include "../../include/headerTP2b.h"


/*
  [insert what this does]

*** Arguments *** 
   t        : type de l'élémnt sur lequel est fait le calcul
   xquad    : points de quadrature sur l'élémnt de ref
   pdsquad  : poids de quadrature associés
   aK       : coordonnées des noeuds d'interpo de l'élémnt actuel K
   matlm    : matrice de la quadrature sur l'élémnt actuel K
   vectelm  : vecteur de quadrature du second membre sur l'élémnt actuel K
*/
void intElem(int t, float** xquad, float* pdsquad, float** aK, float** matelm, float* vectelm){
    //nombre de points de quadrature en fonction du type.
    int q = valq(t);

    float* wx_i = malloc(4*sizeof(float)); //taille 4 parce qu'on a max 4 fonctions de base
    float** dwx_i = aloctab(2,4)
    //boucle sur les points de quadrature
    for(int i=0; i<q; i++){
        
        calFbase(t, x[i], wx_i)
    }
}
