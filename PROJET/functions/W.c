/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 11/02/2026
--------------------------------------------------------------------------------
*/
void W(int nbneel,float coefvar, float *fctbas, float eltdif, float *vecelem){
    for (int i=0; i<nbneel; i++){
        vecelem[i]+=coefvar*eltdif*fctbas[i];
    }
}