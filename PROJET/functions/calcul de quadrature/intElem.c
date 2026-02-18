#include "../../include/headerTP2b.h"

/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 18/02/2026
--------------------------------------------------------------------------------
*/


/*
   Calcule par quadrature, la matrice et le second membre de la formulation variationnelle
   à l'intérieur(pas segment) d'un unique élément K donné

*** Arguments *** 
   t        : type de l'élémnt sur lequel est fait le calcul
   xquad    : points de quadrature sur l'élémnt de ref
   pdsquad  : poids de quadrature associés
   aK       : coordonnées des noeuds d'interpo de l'élémnt actuel K
   matlm    : matrice de la quadrature sur l'élémnt actuel K (initialisé à 0)
   vectelm  : vecteur de quadrature du second membre sur l'élémnt actuel K (initialisé à 0)
*/

//Note : la somme de la quadrature se fait dans les fonctions ADWDW WW WW
//       même d'une itération à l'autre 
// (utilise vectlm[k]+=truc(k) / matelm[k][l]+=truc(k,l))
// attention donc à l'initialiser à 0 avant de l'entrer en argument de intElem

void intElem(int t, int p, int q, float** xquad, float* pdsquad, float** aK, float** matelm, float* vectelm){
    //déclaration des vecteurs et matrices éphémères
    float* wx_i = malloc(4*sizeof(float)); //taille 4 parce qu'on a max 4 fonctions de base
    float** dwx_i = alloctab(4,2);

    float* fk_x = malloc(4*sizeof(float));
    float** JFk = alloctab(4,2);
    float** JFk_inv = alloctab(4,2);

    //matrice des a_alpha_beta(Fk(x_hat))
    float** AabFk = alloctab(2,2);

    //boucle sur les points de quadrature i = 0 -> q-1
    for(int i=0; i<q; i++){
        
        //calculs élémentaires sur le point x_i
        calFbase(t, x[i], wx_i);
        calDerFbase(t, x[i], dwx_i);

        //calcul par transformation Fk(x)
        transFK(aK, wx_i, fk_x, p);
        matJacob(2, aK, dwx_i, JFk);
        float detJFk = invertM2x2(JFk, JFk_inv);
        
        //calcul des a_alpha_beta(Fk(x_hat)) et a00(Fk(x_hat))
        AabFk[0][0] = A11(fk_x); AabFk[0][1] = A12(fk_x);
        AabFk[0][1] = A12(fk_x); AabFk[1][1] = A22(fk_x);
        float A00Fk = A00(fk_x);
        
        //calcul de matelm matrice de l'intérieur en deux parties 
        ADWDW(p, dwx_i, JFk_inv, pdsquad[i]*detJKk, AabFk, matelm)
        WW(p, wx_i, pdsquad[i]*detJKk, A00Fk, matelm);

        //calcul de Fw(Fk(x_hat)) puis de vectelm second membre de l'intérieur
        float fOmgFk = FOMEGA(fk_x);
        W(p, wx_i, pdsquad[i]*detJKk, fOmgFk, vectelm)
    }

    free(wx_i); free(fk_x);
    freetab(JFk); freetab(JFk_inv);
    freetab(dwx_i); freetab(AabFk);
}
