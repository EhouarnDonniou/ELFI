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

    int* sommets = malloc(2*sizeof(int));
    float** coorAr = alloctab(2,2);

    //cas général, calculs intérieurs à l'élément K actuel
    intElem(typeEl, nbneel, nbaret, xquad, pdsquad, coorEl, MatElem, SMbrElem);

    //Boucles sur les nbaret arêtes de l'élément actuel
    //Pour prise en compte des conditions au bord
    //
    // intérieur -> on fait rien
    // bord Dirichlet homogène ->
    // bord Dirichlet non-homogène ->
    // bord Neumann/Fourier ->
    for(int i=1; i<=nbaret;i++){
        numNaret(&i,sommets,typeEl);
        selectPts(2,sommets,coorEl,coorAr);

        
        if (nrefArEl[i-1] == nRefDom); //noeud à l'intérieur => "on fait rien"
        else{
            for (int j=0;j<nbRefD0;j++){
                if (nrefArEl[i-1]==numRefD0[j]){
                    NuDElem[sommets[0]-1]=0;NuDElem[sommets[1]-1]=0;
                    uDElem[sommets[0]-1]=0; uDElem[sommets[1]-1]=0;
                }
            }
            for (int j=0;j<nbRefD1;j++){
                if (nrefArEl[i-1]==numRefD1[j]){
                    NuDElem[sommets[0]-1]=-1;NuDElem[sommets[1]-1]=-1;
                    uDElem[sommets[0]-1]=UD(coorAr[0]);
                    uDElem[sommets[1]-1]=UD(coorAr[1]); 
                }
            }
            for (int j=0;j<nbRefF1;j++){
                if (nrefArEl[i-1]==numRefF1[j]){

                    //hardcode type = 3 et nbaret = 1;
                    //appel intAret(__);

                    uDElem[sommets[0]-1]=0; uDElem[sommets[1]-1]=0;
                }


            }
        }

        // injection au bon endroit des résultats dans MatElem et SMbrElem
    }
    freetab(xquad); free(pdsquad);
}