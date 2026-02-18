/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 11/02/2026
--------------------------------------------------------------------------------
*/
//cofvar est la matrice des a_alpha_beta(Fk(x_k_hat))
//DerFbase est la matrice de la dérivées des fonctions de base
void ADWDW(int nbneel, float **DerFbase, float eltdif, float **cofvar, float **matelm) {
  int i, j;
  float coeff;
  for(int alpha=0;aplha<2;alpha++){
    for(int beta=0;beta<2;beta++){
        for (i=0; i<nbneel; i++) {
            coeff = eltdif*cofvar[alpha][beta]*DerFbase[alpha][i];
            for (j=0; j<nbneel; j++) {
                matelm[i][j] = matelm[i][j] + coeff*DerFbase[beta][j];
            }
        }
    }
  }
  
}