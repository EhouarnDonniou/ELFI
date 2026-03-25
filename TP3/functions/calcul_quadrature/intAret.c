/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 20/03/2026
--------------------------------------------------------------------------------
*/

#include "../../include/headerTP2b.h"
#include "../../include/headerTP2a.h"
#include "../../include/headerTP2b.h"
#include "../../include/utilitaires.h"

/*
   Calcule par quadrature, la matrice et le second membre de la formulation variationnelle
   à l'intérieur(pas segment) d'un unique élément K donné

*** Arguments *** 
   t        : type de l'élémnt sur lequel est fait le calcul
   p        : nombre de noeuds d'interpo géomértrique qui forment l'élémnt K
   q        : nombre d'arêtes qui forment l'élémnt K
   xquad    : points de quadrature sur l'élémnt de ref
   pdsquad  : poids de quadrature associés
   aK       : coordonnées des noeuds d'interpo de l'élémnt actuel K
   matlm    : matrice de la quadrature sur l'élémnt actuel K (initialisé à 0)
   vectart  : vecteur de quadrature du second membre sur l'élémnt actuel K (initialisé à 0)
*/

//Note : la somme de la quadrature se fait dans les fonctions WW WW même d'une itération à l'autre 
// (utilise vectart[k]+=truc(k) / matart[k][l]+=truc(k,l))
// attention donc à l'initialiser à 0 avant de l'entrer en argument de intAret

void intAret(int t, int p, int q, float** xquad, float* pdsquad, float** aK, float** matart, float* vectart){
    //déclaration des vecteurs et matrices éphémères
    float* wx_i = malloc(q*sizeof(float));
    float** dwx_i = alloctab(q,2);

    float* fk_x = malloc(2*sizeof(float));
    float** JFk = alloctab(1,2);
    float** JFk_inv = alloctab(1,2); 

    //boucle sur les points de quadrature i = 0 -> q-1
    for(int i=0; i<q; i++){
        //réinitialisation de la jacobienne à 0.
        JFk[0][0]=0;JFk[0][1]=0;

        //fonctions de base et dérivées associées sur le segment de référence
        calFbase(t, xquad[i], wx_i);
        calDerFbase(t, xquad[i], dwx_i);

        //élément de longueur
        matJacob(t, aK, dwx_i, JFk);
        float LK = sqrtf(JFk[0][0]*JFk[0][0] + JFk[0][1]*JFk[0][1]); //norme 2 du vecteur JFk

        //image du point de quad dans K
        transFK(aK, wx_i, fk_x, p);

        float eltdif = pdsquad[i]*LK;

        //contribution au point de quadrature courant pour le calcul des intégrales 
        //calcul de BN(Fk(x_hat)) puis de matart
        float BNFk = BN(fk_x);
        WW(p, wx_i, eltdif, BNFk, matart);

        //calcul de FN(Fk(x_hat)) puis de vectart second membre 
        float FNFk = FN(fk_x);
        W(p, wx_i, eltdif, FNFk, vectart);
    }
    free(wx_i); freetab(dwx_i); free(fk_x); 
    freetab(JFk); freetab(JFk_inv);
}
