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