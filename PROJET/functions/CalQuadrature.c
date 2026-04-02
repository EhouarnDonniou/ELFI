#include "../include/headerTP1.h"
#include "../include/headerTP2a.h"
#include "../include/headerTP2b.h"
#include "../include/utilitaires.h"

/*
Contient les fonctions : 
    -W, WW, ADWDW 
    -transFk, calFbase, calDerFbase
    -valq, ppquad
    -matJacob, invertM2x2
*/

/*
--------------------------------------------------------------------------------
  Mise a jour de la matrice elementaire : ajout de la contribution
  d'un point de quadrature d'un element ou de son bord, pour le calcul
  d'integrales elementaires faisant intervenir le produit de deux
  fonctions de base.

  Terminologie : FK designe la transformation qui calcule l'image dans
                 l'element courant d'un point de l'element de reference

  Arguments d'entree :
   nbneel : nombre de noeuds de l'element
   fctbas : valeurs des fonctions de base au point de quadrature courant
            Dimensions utiles : fctbas(nbneel)
   eltdif : element differentiel multiplie par le poids de quadrature
   cofvar : valeur du coefficient variable (fonction a integrer calculee
            en l'image par FK du point de quadrature courant)
   matelm : matrice elementaire de masse a actualiser
            Dimensions utiles : matelm(nbneel,nbneel)
  Arguments de sortie :
   matelm : matrice elementaire de masse actualisee
--------------------------------------------------------------------------------
*/

void WW(int nbneel, float *fctbas, float eltdif, float cofvar, float **matelm) {
  int i, j;
  float coeff;

  for (i=0; i<nbneel; i++) {
    coeff = eltdif*cofvar*fctbas[i];
    for (j=0; j<nbneel; j++) {
      matelm[i][j] = matelm[i][j] + coeff*fctbas[j];
    }
  }
}


/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 11/02/2026
--------------------------------------------------------------------------------
*/


//cofvar est la matrice des a_alpha_beta(Fk(x_k_hat))
//DW est la matrice de la dérivées des fonctions de base
void ADWDW(int nbneel, float **DW, float** JFk_inv, float eltdif, float **cofvar, float** matelm) {
  int i, j;
  float coeff;

  //dwi/dx_alpha(Fk(x_hat)) = (grad wi_hat(x_hat))T * (inv(JFk)(Fk(x_hat)))_alpha
  //same pour (j,beta)
  float dwdx_fk_xhat;

  for(int alpha=0;alpha<2;alpha++){
    for(int beta=0;beta<2;beta++){
      
      for (i=0; i<nbneel; i++) {
        dwdx_fk_xhat = DW[i][0]*JFk_inv[alpha][0] + DW[i][1]*JFk_inv[alpha][1];
        coeff = eltdif*cofvar[alpha][beta]*dwdx_fk_xhat;
        for (j=0; j<nbneel; j++) {
          dwdx_fk_xhat = DW[j][0]*JFk_inv[beta][0] + DW[j][1]*JFk_inv[beta][1];
          matelm[i][j] = matelm[i][j] + coeff*dwdx_fk_xhat;
        }
      }
    }
  }
}


/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 11/02/2026
--------------------------------------------------------------------------------
*/

void W(int nbneel, float *fctbas, float eltdif, float coefvar, float *vectelm){
    for (int i=0; i<nbneel; i++){
        vectelm[i]+=coefvar*eltdif*fctbas[i];
    }
}


/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 01/02/2026
--------------------------------------------------------------------------------
*/


/*
    Pour l'élément actuel K, calcul la valeur de FK(x_hat)
    Transformation vers l'élément de référence K_hat

*** Arguments *** 
    pcoord_a    : coordonnées du point actuel aK pour K l'élémnt actuel
    pvalfbase   : valeurs des fonctions de base sur K_hat (calculées au préalable)
    fk_x        : résultat de la fonction FK(x_hat) pour K l'élémnt actuel (initialisé à 0 avant appel)
    p           : nombre de fonctions de base

*/
void transFK(float** pcoord_a, float* pvalfbase, float* fk_x, int p){
    for(int i=0; i<p; i++){
        fk_x[0] += pvalfbase[i] * pcoord_a[i][0];
        fk_x[1] += pvalfbase[i] * pcoord_a[i][1];
    }
}

/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 28/01/2026
--------------------------------------------------------------------------------
*/


/*
    Calcul de wi(x) pour x dans K et wi fonction de base sur K
    Les wi sont d'ordre 1 tq wi(sommet_j)=1 si j==i
                                         =0 si j!=i 

*** Arguments ***
    t       : type de l'élément actuel K
    x       : coordonnées du point x_hat de référence actuel
    valeurs : valeurs des fonctions de base sur l'élémnt K_hat au point x_hat

*/
void calFbase(int t, float* x, float* valeur){
    switch(t){
        //quadrangles -> ordre 1 : Q1
        case(1):
            valeur[0] = x[0]-x[0]*x[1];
            valeur[1] = x[0]*x[1];
            valeur[2] = x[1]-x[0]*x[1];
            valeur[3] = 1 -x[1] -x[0] + x[0]*x[1];
            break;
        //triangles -> ordre 1 : P1
        case(2):
            valeur[0] = x[0];
            valeur[1] = x[1];
            valeur[2] = 1-x[0]-x[1];
            break;
        //segments
        case(3):
            valeur[0] = *x;
            valeur[1] = -(*x)+1;
            break;
    }
}


/*
    Calcul de dwi/dxj(x) pour x dans K et wi fonction de base sur K
    Pour K dans le plan, x = (x1,x2)

*** Arguments ***
    t       : type de l'élément actuel K
    x       : coordonnées du point x_hat de référence actuel
    valeurs : valeurs des dérivées partielles des fonctions de base sur l'élémnt K_hat au point x_hat

*/

void calDerFbase(int t, float* x, float** valeur){
    switch(t){
        //quadrangles
        case(1):
            valeur[0][0] = 1-x[1]; 
            valeur[0][1] = -x[0];

            valeur[1][0] = x[1];
            valeur[1][1] = x[0];

            valeur[2][0] = -x[1];
            valeur[2][1] = 1-x[0];
            
            valeur[3][0] = -1 + x[1];
            valeur[3][1] = -1 + x[0];
            break;
        //triangles 
        case(2):
            valeur[0][0] = 1;
            valeur[0][1] = 0;

            valeur[1][0] = 0;
            valeur[1][1] = 1;

            valeur[2][0] = -1;
            valeur[2][1] = -1;
            break;
        //segments
        case(3):
            valeur[0][0] = 1;
            valeur[1][0] = -1;
            break;
    }
}


/*
--------------------------------------------------------------------------------
    Dora PAPAI, Ehouarn DONNIOU, Damien MALETTE

    Ecrit le 04/03/2026
--------------------------------------------------------------------------------
*/

int valq(int t){    
    if(t==1) return 9;
    else return 3;
}

void ppquad(int t, float* poids, float** pts){
    switch (t){
        // quadrangle (ordre 3) q=9
        case 1 : 
            //vecteur poids
            for(int i=0; i<5; i++){
                poids[i]=1./36.;
            }
            for(int i=4; i<8; i++){
                poids[i]=1./9.;
            }
            poids[8]=4./9.;
        
            //matrice des points de quadrature
            pts[0][0]=1.; pts[0][1]=0.;   //x1
            
            pts[1][0]=1.; pts[1][1]=1.;   //x2
            
            pts[2][0]=0.; pts[2][1]=1.;   //x3
            
            pts[3][0]=0.; pts[3][1]=0.;   //x4
            
            pts[4][0]=1.; pts[4][1]=0.5;   //x5
            
            pts[5][0]=0.5;pts[5][1]=1.;  //x6
            
            pts[6][0]=0.; pts[6][1]=0.5;   //x7
            
            pts[7][0]=0.5;pts[7][1]=0.;  //x8

            pts[8][0]=0.5;pts[8][1]=0.5;  //x9
            break;

        // triangle (orde 2) q=3
        case 2 : 
            //vecteur poids
            for(int i=0; i<3; i++){
                poids[i]= 1./6.;
            }           
            //matrice des points de quadrature
            pts[0][0]=0.5;pts[0][1]=0.5;  //x1
            
            pts[1][0]=0.; pts[1][1]=0.5;   //x2
            
            pts[2][0]=0.5;pts[2][1]=0.;  //x3
            break;

        // segment (ordre 3) q=3
        case 3 : 

            //vecteur poids
            poids[0]=1./6.;
            poids[1]=1./6.;
            poids[2]=2./3.;

            //matrice des points de quadrature
            pts[0][0]=1.;    //x1
            pts[1][0]=0.;    //x2
            pts[2][0]=0.5;  //x3
            break;
    }//x3

}



/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 11/02/2026
--------------------------------------------------------------------------------
*/


/*
    Calcule la matrice Jacobienne de FK(x_hat) pour K actuel en un point x_hat donné (x_hat dans K_hat)
    Utilise la formule pour x_hat noté x : 
                  
            (dFK/dx_j)(x) = Somme(l = 1:5-t)[aK_l * (dw_l/dx_j)(x)] , dans R^2

    On a donc (JFK(x))_i,j = (dFK_i/dx_j)(x) pour i,j = 1,2

*** Arguments *** 
    t    : type de l'élémnt actuel K
    aK   : coordonnées des noeuds d'interpo de l'élémnt actuel K
    derW : liste de valeurs des dw/dxi(x_hat) pour x_hat actuel.
    Jac  : matrice jacobienne de FK(x_hat)     pour t==2,3 (initialisé à 1 avant chaque appel)
           vecteur (dFK/dx_1, dFK/dx_2)(x_hat) pour t==1 

*/
void matJacob(int t, float* aK[], float** derW, float** Jac){
    
    int stop = 5 - t; 
    //condition d'arrêt : stop = 5-t = #points d'interpolation de chaque élément
    //  -> quadrangles  : stop = 5-1 = 4 
    //  -> triangles    : stop = 5-2 = 3
    //  -> segments     : stop = 5-3 = 2

    if(t==3){ //segments
        for(int i=0; i<stop; i++){
            Jac[0][0] += derW[i][0]*aK[i][0];
            Jac[0][1] += derW[i][0]*aK[i][1]; 
            
        }
    }
    else{ //triangle et quadrangles
        for(int i=0; i<stop; i++){
            Jac[0][0] += derW[i][0]*aK[i][0];
            Jac[1][0] += derW[i][0]*aK[i][1];
            Jac[0][1] += derW[i][1]*aK[i][0];
            Jac[1][1] += derW[i][1]*aK[i][1];
        }
    }
}

/*
    Calcule le déterminant d'une matrice 2x2.
    Inverse la matrice et retourne le déterminant.

*** Arguments *** 
  in-
    Mat     : matrice 2x2 à inverser
    Mat_inv : matrice 2x2 inverse de Mat 
  out-
    determinant : déterminant de la matrice Mat inversée 

*** edge case *** 
      det(Mat)=0 => determinant = 0 et mat n'est pas inversée (Mat_inverse non-modifiée)

*/
float invertM2x2(float** Mat, float** Mat_inv){

    float determinant = Mat[0][0]*Mat[1][1] - Mat[0][1]*Mat[1][0];

    if(fabs(determinant)<=  pow(10,-8) ){
        printf("/! ERROR \n La matrice n'est pas inversible!\n");
        return 0;
    }
    
    Mat_inv[0][0] = Mat[1][1]/determinant;
    Mat_inv[1][1] = Mat[0][0]/determinant;
    Mat_inv[0][1] = -Mat[0][1]/determinant;
    Mat_inv[1][0] = -Mat[1][0]/determinant;

    return(determinant);
}