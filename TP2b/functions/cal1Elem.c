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
    float* pdsquad_ar = malloc(3*sizeof(float));
    float** xquad_ar = alloctab(3,2);
    ppquad(3,pdsquad_ar,xquad_ar);

    //cas général, calculs intérieurs à l'élément K actuel
    intElem(typeEl, nbneel, nbaret, xquad, pdsquad, coorEl, MatElem, SMbrElem);

    //Boucles sur les nbaret arêtes de l'élément actuel
    //Pour prise en compte des conditions au bord
    //
    // intérieur -> on fait rien
    // bord Neumann/Fourier -> gestion par appel de intAret
    // bord Dirichlet homogène ->
    // bord Dirichlet non-homogène ->
    for(int i=1; i<=nbaret;i++){
        numNaret(&i,sommets,typeEl);
        selectPts(2,sommets,coorEl,coorAr);

        
        if (nrefArEl[i-1] == nRefDom); //noeud à l'intérieur => "on fait rien"
        else{
            for (int j=0;j<nbRefF1;j++){
                if (nrefArEl[i-1]==numRefF1[j]){
                    uDElem[sommets[0]-1]=0; uDElem[sommets[1]-1]=0; //-> pas nécéssaire

                    float* VectAret = malloc(2*sizeof(float));
                    float** MatAret = alloctab(2,2);

                    //il faut les init à 0 à chaque appel
                        for(int k=0; k<2 ; k++){
                            VectAret[k]=0;
                            for(int l=0; l<2; l++){
                                MatAret[k][l]=0;
                            }
                        }

                    intAret(3, 2, 3, xquad_ar, pdsquad_ar,coorAr, MatAret, VectAret);
                    
                    for(int k=0; k<2 ; k++){
                        int nk = sommets[k]-1;
                        SMbrElem[nk] = SMbrElem[nk] + VectAret[k];
                            for(int l=0; l<2; l++){
                                int nl = sommets[l]-1;
                                MatElem[nk][nl] = MatElem[nk][nl] + MatAret[k][l];
                            }
                        }
                    
                    free(VectAret); freetab(MatAret);
                    
                }
            }
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
            
        }
    }
    freetab(xquad); free(pdsquad); free(sommets);
    free(pdsquad_ar);freetab(xquad_ar);
    free(coorAr);//free simple parce que ça pointe sur un espace mémoire aussi pointé par coorEl.
                 //si on libère ces addresses, elle ne sont pas accessibles à coorEl.
    
}