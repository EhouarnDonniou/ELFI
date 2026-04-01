#include "../include/headerTP1.h"
#include "../include/headerTP2a.h"
#include "../include/headerTP2b.h"
#include "../include/utilitaires.h"

/*
Contient les fonctions : 
    -Cal1Elem
    -intElem, intAret 
    -numNaret, selectPts
*/


/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 04/03/2026
--------------------------------------------------------------------------------
*/

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

    //construction du contexte de quadrature (points et poids associés) pour intElem
    int nbquad = valq(typeEl);
    float* pdsquad = malloc(nbquad*sizeof(float));
    float** xquad = alloctab(nbquad,2);
    ppquad(typeEl,pdsquad,xquad);

    //cas général, calculs intérieurs à l'élément K actuel
    intElem(typeEl, nbneel, nbaret, xquad, pdsquad, coorEl, MatElem, SMbrElem);


    //construction du contexte de quadrature (points et poids associés) pour intAret
    int* sommets = malloc(2*sizeof(int));
    float** coorAr = alloctab(2,2);
    float* pdsquad_ar = malloc(3*sizeof(float));
    float** xquad_ar = alloctab(3,2);
    ppquad(3,pdsquad_ar,xquad_ar);

    //Boucles sur les nbaret arêtes de l'élément actuel
    //Pour prise en compte des conditions au bord
    //
    // intérieur -> on ne fait rien
    // bord Neumann/Fourier -> gestion par appel de intAret, uDElem = 0
    // bord Dirichlet homogène -> NuDElem = 0, uDElem = 0
    // bord Dirichlet non-homogène -> NuDElem = -1, uDElem = uD(x)
    for(int i=1; i<=nbaret;i++){

        //correspondance : 
        // num arête i <-> num sommets (na,nb) <-> coordonnées des sommets parmis les points de K [(xa,ya),(xb,yb)]
        numNaret(&i,sommets,typeEl);
        selectPts(2,sommets,coorEl,coorAr);

        
        if (nrefArEl[i-1] == nRefDom); //noeud à l'intérieur => "on ne fait rien"
        else{
            //boucle sur les num de ref des bords sous condition de Fourier/Neumann
            //puis condition if pour vérifier si l'arête est référencée de la même manière
            for (int j=0;j<nbRefF1;j++){
                if (nrefArEl[i-1]==numRefF1[j]){
                    uDElem[sommets[0]-1]=0; uDElem[sommets[1]-1]=0;

                    float* VectAret = malloc(2*sizeof(float));
                    float** MatAret = alloctab(2,2);

                    //il faut les init à 0 à chaque appel
                        for(int k=0; k<2 ; k++){
                            VectAret[k]=0;
                            for(int l=0; l<2; l++){
                                MatAret[k][l]=0;
                            }
                        }
                    
                    //appel à intAret, intègrales linéaires sur les arêtes dans gammaN
                    intAret(2, 3, xquad_ar, pdsquad_ar,coorAr, MatAret, VectAret);
                    
                    for(int k=0; k<2 ; k++){
                        int nk = sommets[k]-1;
                        SMbrElem[nk] = SMbrElem[nk] + VectAret[k];
                            for(int l=0; l<2; l++){
                                int nl = sommets[l]-1;
                                MatElem[nk][nl] = MatElem[nk][nl] + MatAret[k][l];
                            }
                    }
                    //libération ici pour les réallouer si on re-rentre dans la condition 
                    free(VectAret); freetab(MatAret);
                }
            }
            //boucle sur la liste des num ref Dirichlet homogène
            for (int j=0;j<nbRefD0;j++){
                if (nrefArEl[i-1]==numRefD0[j]){
                    NuDElem[sommets[0]-1]=0;//NuDElem[sommets[1]-1]=0;
                    uDElem[sommets[0]-1]=0; //uDElem[sommets[1]-1]=0;
                }
            }
            //boucle sur la liste des num ref Dirichlet non-homogène 
            for (int j=0;j<nbRefD1;j++){
                if (nrefArEl[i-1]==numRefD1[j]){
                    NuDElem[sommets[0]-1]=-1; NuDElem[sommets[1]-1]=-1;

                    //utilisation de UD pour les points dans cette arête
                    uDElem[sommets[0]-1]=UD(coorAr[0]);
                    uDElem[sommets[1]-1]=UD(coorAr[1]); 
                }
            }
        }
    } 
    //Libération de la mémoire
    freetab(xquad); free(pdsquad); free(sommets);
    free(pdsquad_ar);freetab(xquad_ar);
    free(coorAr);//free simple parce que ça pointe sur un espace mémoire aussi pointé par coorEl.
                 //si on libère ces addresses, elle ne sont pas accessibles à coorEl.
    
}


/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 18/02/2026
--------------------------------------------------------------------------------
*/

/*
   Calcule par quadrature, la matrice et le second membre de la formulation variationnelle
   à l'intérieur(pas segment) d'un unique élément K donné

*** Arguments *** 
   t        : type de l'élémnt actuel K
   p        : nombre de noeuds d'interpo géomértrique qui forment l'élémnt K
   q        : nombre d'arêtes qui forment l'élémnt K
   xquad    : points de quadrature sur l'élémnt de ref
   pdsquad  : poids de quadrature associés
   aK       : coordonnées des noeuds d'interpo de l'élémnt actuel K
   matlm    : matrice de la quadrature sur l'élémnt actuel K (initialisé à 0)
   vectelm  : vecteur de quadrature du second membre sur l'élémnt actuel K (initialisé à 0)
*/

//Note : la somme de la quadrature se fait dans les fonctions ADWDW WW WW
//       même d'une itération à l'autre 
// (utilise vectlm[k]+=truc(k) / matelm[k][l]+=truc(k,l))
// attention donc à l'initialiser à 0 avant de l'entrer en argument de intElem

void intElem(int t, int p, int q, float** xquad, float* pdsquad, float** aK, float** matelm, float* vectelm){

    //déclaration des vecteurs et matrices éphémères
    float* wx_i = malloc(q*sizeof(float)); //taille 4 parce qu'on a max 4 fonctions de base
    float** dwx_i = alloctab(q,2);

    float* fk_x = malloc(2*sizeof(float));
    float** JFk = alloctab(2,2);
    float** JFk_inv = alloctab(2,2);

    //matrice des a_alpha_beta(Fk(x_hat))
    float** AabFk = alloctab(2,2);

    int q_quad = valq(t);
    //boucle sur les points de quadrature i = 0 -> q-1
    for(int i=0; i<q_quad; i++){

        //réinitialisation de la jacobienne à 0.
        for(int j=0; j<2;j++){
            JFk[j][0]=0;
            JFk[j][1]=0;
        }
        //calculs élémentaires sur le point x_i
        calFbase(t, xquad[i], wx_i);
        calDerFbase(t, xquad[i], dwx_i);

        //calcul par transformation Fk(x)
        transFK(aK, wx_i, fk_x, p);
        matJacob(t, aK, dwx_i, JFk); 

        float detJFk = invertM2x2(JFk, JFk_inv);

        //calcul des a_alpha_beta(Fk(x_hat)) et a00(Fk(x_hat))
        AabFk[0][0] = A11(fk_x); AabFk[0][1] = A12(fk_x);
        AabFk[0][1] = A12(fk_x); AabFk[1][1] = A22(fk_x);
        float A00Fk = A00(fk_x);
        
        float eltdif = pdsquad[i]*detJFk;

        //calcul de matelm matrice de l'intérieur en deux parties
        ADWDW(p, dwx_i, JFk_inv, eltdif, AabFk, matelm);
        WW(p, wx_i, eltdif, A00Fk, matelm);
        //calcul de Fw(Fk(x_hat)) puis de vectelm second membre de l'intérieur
        float fOmgFk = FOMEGA(fk_x);
        W(p, wx_i, eltdif, fOmgFk, vectelm);
    }
    free(wx_i); free(fk_x);
    freetab(JFk); freetab(JFk_inv);
    freetab(dwx_i); freetab(AabFk);
}

/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 20/03/2026
--------------------------------------------------------------------------------
*/

/*
   Calcule par quadrature, la matrice et le second membre de la formulation variationnelle
   à l'intérieur(pas segment) d'un unique élément K donné

*** Arguments *** 
   p        : nombre de noeuds d'interpo géomértrique qui forment le segment actuel K'
   q_quad   : nombre de points de quadrature sur le segment actuel K'
   xquad    : points de quadrature sur le segment de ref
   pdsquad  : poids de quadrature associés
   aK       : coordonnées des noeuds d'interpo du segment actuel K'
   matart   : matrice de la quadrature sur le segment actuel K' (initialisé à 0)
   vectart  : vecteur de quadrature du second membre sur le segment actuel K' (initialisé à 0)
*/

//Note : la somme de la quadrature se fait dans les fonctions WW WW même d'une itération à l'autre 
// (utilise vectart[k]+=truc(k) / matart[k][l]+=truc(k,l))
// attention donc à l'initialiser à 0 avant de l'entrer en argument de intAret

void intAret(int p, int q_quad, float** xquad, float* pdsquad, float** aK, float** matart, float* vectart){
    //déclaration des vecteurs et matrices éphémères
    float* wx_i = malloc(q_quad*sizeof(float));
    float** dwx_i = alloctab(q_quad,2);

    float* fk_x = malloc(2*sizeof(float));
    float** JFk = alloctab(1,2);
    float** JFk_inv = alloctab(1,2); 

    //boucle sur les points de quadrature i = 0 -> q_quad-1
    for(int i=0; i<q_quad; i++){
        //réinitialisation de la jacobienne à 0.
        JFk[0][0]=0;JFk[0][1]=0;

        //fonctions de base et dérivées associées sur le segment de référence
        calFbase(3, xquad[i], wx_i);
        calDerFbase(3, xquad[i], dwx_i);

        //élément de longueur
        matJacob(3, aK, dwx_i, JFk);
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


/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 04/02/2026
--------------------------------------------------------------------------------
*/

// attention à ne pas appliquer aux segments (t=3)
/*
    Prend le numéro local d'une arête et ressort le couple de numéros locaux des sommets associés
    en fonction du type de l'élément et ordonné en sens anti-horaire (numérotation locale de ref)

*** Arguments ***
    numaret    : numéro local de l'arête actuelle
    t          : type de l'élément actuel (t==1 -> quadrangle, t==2 -> triangle)
    numsommet[]: le couple (_,_), numéros locaux des sommets de l'arête en entrée

*/
void numNaret(int* numaret, int numsommets[], int t){
    switch(*numaret){
        case(1): 
        //num-arête == 1 -> sommets : (1,2)
            numsommets[0]=1;
            numsommets[1]=2;
            break;
        case(2):
        //num-arête == 2 -> sommets : (2,3)
            numsommets[0]=2;
            numsommets[1]=3;
            break;
        case(3):
        //num-arête == 3 
            if(t==1){ //quadrangle
            //-> sommets : (3,4)
                numsommets[0]=3;
                numsommets[1]=4;
            }
            if(t==2){ //triangle
            //-> sommets : (3,1)
                numsommets[0]=3;
                numsommets[1]=1;
            }
            break;
        case(4): //uniquement pour le quadrangle
        //num-arête == 4 -> sommets : (4,1)
            numsommets[0]=4;
            numsommets[1]=1;
            break;
    }
}
//normalement aucun check à passer pour vérifier le conflit t==1 et *numaret==4
//on part du principe que si t==1, on ne transmettra pas *numaret==4 à la fonction 



/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 04/02/2026
--------------------------------------------------------------------------------
*/

/*
    Associe le num global num[] de nb points à leurs coordonées coorSel[]
    En passant par la "liste" de toutes le coordonnées coorEns (ordonnée croissant par num globale)

*** Arguments ***
    nb        : nombre de points séléctionnés
    num[]     : liste des numéros globaux de chaque point
    coorEns[] : pointeur vers les coordonnées(pointeur 1x2) des points
                rangés par ordre croissant de la numérotation globale
    coorSel[] : pointeur vers les coordonnées(pointeur 1x2) des points séléctionnés
                pointe aux mêmes endroits de la mémoire que coorEns, 
                pour seulement les points séléctionnés associés par leur numéro global.
*/

void selectPts(int nb, int num[], float* coorEns[], float* coorSel[]){
    for(int i=0; i<nb; i++){
        coorSel[i] = coorEns[num[i]-1]; //-1 car les num globaux sont >=1
    }
}