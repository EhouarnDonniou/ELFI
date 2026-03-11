/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 04/03/2026
--------------------------------------------------------------------------------
*/

#include "../include/headerTP1.h"
#include "../include/headerTP2a.h"
#include "../include/headerTP2b.h"
#include "../include/utilitaires.h"


//tous les --Elem sont initialisés à 0 avant l'appel
void cal1Elem(int nRefDom, int nbRefD0, int* numRefD0, int nbRefD1, int* numRefD1, int nbRefF1, int* numRefF1, int typeEl, int nbneel, float** coorEl, int nbaret, int* nrefArEl, float** MatElem, float* SMbrElem, float* NuDElem, float* uDElem){

    //construction du contexte de quadrature (points et poids associés)
    int nbquad = valq(typeEl);
    float* pdsquad = malloc(nbquad*sizeof(float));
    float** xquad = alloctab(2,nbquad);
    ppquad(typeEl,pdsquad,xquad);

    intElem(typeEl, nbneel, nbaret, xquad, pdsquad, coorEl, MatElem, SMbrElem)
    //appel intAret(----)
}