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

/*
   Construit la matrice et le second membre associés à un élément K actuel
   MatElem/VectElem sont d'abord construite par appel à intElem 

   Les conditions de bord Neumann/Fourier sont calculées par appel à intAret
   puis injectées dans MatElem/VectElem

   Les conditions de Dirichlet sont calculées et injectées dans MatElem/VectElem à la fin
*** Arguments *** 

   nRefDom  : 
   nbRefD0, numRefD0 : 
   nbRefD1, numRefD1 : 
   nbRefF1, numRefF1 :
   typeEl   :
   nbneel   : 
   coorEl   : 
   nbaret   : 
   nrefArEl : 
   MatElem  : 
   SMbrElem : 
   NuDElem  : 
   uDElem   : 
   
*/

//tous les --Elem sont initialisés à 0 avant l'appel
void cal1Elem(int nRefDom, int nbRefD0, int* numRefD0, int nbRefD1, int* numRefD1, int nbRefF1, int* numRefF1, int typeEl, int nbneel, float** coorEl, int nbaret, int* nrefArEl, float** MatElem, float* SMbrElem, int* NuDElem, float* uDElem){

    //construction du contexte de quadrature (points et poids associés)
    int nbquad = valq(typeEl);
    float* pdsquad = malloc(nbquad*sizeof(float));
    float** xquad = alloctab(nbquad,2);
    ppquad(typeEl,pdsquad,xquad);

    intElem(typeEl, nbneel, nbaret, xquad, pdsquad, coorEl, MatElem, SMbrElem);
    //appel intAret(----)
    //prise en compte des conditions de Dirichlet
    for(int i=0; i<nbaret;i++){
        if (nrefArEl[i] == nRefDom){}
        else{
            for (int j=0;j<nbRefD0;j++){
                if (nrefArEl[i]==numRefD0[j]){
                    NuDElem[i]=0;
                    uDElem[i]=;
                }
            }
            for (int j=0;j<nbRefD1;j++){
                if (nrefArEl[i]==numRefD1[j]){
                    NuDElem[i]=-1;
                    uDElem[i]=;
                }
            }
        }
    }
}