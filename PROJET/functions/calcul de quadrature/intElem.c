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

    //boucle sur les points de quadrature
    for(int i=0; i<q; i++){
        float* wx_i
        calFbase(t, x[i], wx_i)
    }
}
