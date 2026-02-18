/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 11/02/2026
--------------------------------------------------------------------------------
*/
//cofvar est la matrice des a_alpha_beta(Fk(x_k_hat))
//DW est la matrice de la dérivées des fonctions de base
void ADWDW(int nbneel, float **DW, float** JFk_inv, float eltdif, float **cofvar, float **matelm) {
  int i, j;
  float coeff;

  //dwi/dx_alpha(Fk(x_hat)) = (grad wi_hat(x_hat))T * (inv(JFk)(Fk(x_hat)))_alpha
  //same pour (j,beta)
  float dwdx_fk_xhat;

  for(int alpha=0;aplha<2;alpha++){
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