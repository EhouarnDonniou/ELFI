/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 02/04/2026
--------------------------------------------------------------------------------
*/


//pour compiler : bash compil.sh dans le dossier actuel

#include <stdio.h>
#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/headerTP3_4.h"
#include "include/headerTP5.h"
#include "include/forfun.h"
#include "include/utilitaires.h"
#include "include/dsmoapr.h"

void main(){
//déclaration-init pour la lecture de fichiers
    char* ficmai = "input/car3x3t_3";
    printf("Lecture du fichier %s\n\n",ficmai);
    //printf("\nDonner le nom du fichier de maillage : ");
    //scanf("%s", ficmai); 
    //printf("tout est lu correctement\n");
    char* ficRef = "input/NUMREF.Test";
    printf("Lecture du fichier %s\n\n",ficRef);
    int affichage;
    printf("Voulez-vous afficher les résultats ?\n");
    printf(" Aucun affichage : 0\n Affichage SMD : 1\n Affichage SMD-SMO : 2\n Affichage SMD-SMO-Profile : 3\n");
    scanf("%d", &affichage); 

//déclaration des variables géométriques
    float** coord;
    int** ngnel; 
    int typeEl, nbtng, nbtel, nbneel, nbaret;

//déclaration des variables relatives aux conditions de bord
    int** nRefAr;
    int nRefDom, nbRefD0, nbRefD1, nbRefF1;
    int* numRefD0;
    int* numRefD1;
    int* numRefF1;

//appel des fonctions de lecture de fichiers pour initialiser les variables associées au maillage/domaine
    int check = lecfima(ficmai,&typeEl,&nbtng,&coord,&nbtel,&ngnel,&nbneel,&nbaret,&nRefAr);
    
    lecNumRef(ficRef,&nRefDom,&nbRefD0,&nbRefD1,&nbRefF1,&numRefD0,&numRefD1,&numRefF1);

    

//declaration et initialisation des variables relatives au stockage morse désordonné
    float* SecMembre = malloc(nbtng*sizeof(float));
    int* NumDLDir = malloc(nbtng*sizeof(int));
    float* ValDLDir = malloc(nbtng*sizeof(int));
    int* AdPrCoefLi = malloc(nbtng*sizeof(int)); int NbCoef = 12*nbtng; //on overshoot
    float* Matrice = malloc((nbtng+NbCoef)*sizeof(float));
    int* NumCol = malloc(NbCoef*sizeof(int));
    int* AdSuccLi = malloc(NbCoef*sizeof(int));
    int NextAd;

//assemblage du système linéaire (matrices élémentaires, assemblage SMD)
    Assemblage(nRefDom,nbRefD0,numRefD0,nbRefD1,numRefD1,nbRefF1,numRefF1,
            coord ,ngnel ,nRefAr ,typeEl ,nbtng ,nbtel ,nbneel ,nbaret ,
            nbtng ,NbCoef ,SecMembre ,NumDLDir ,ValDLDir ,AdPrCoefLi ,Matrice ,NumCol ,AdSuccLi, &NextAd);

//affichage système assemblé en SMD
if (affichage>=1){
    affsmd_(&nbtng, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, NumDLDir, ValDLDir);
}


//declaration d    free(Profil_true); free(MatProf_true);es variables relatives au stockage morse ordonné
    NbCoef = AdPrCoefLi[nbtng-1];
    float* SecMemb0 = malloc(nbtng*sizeof(float));
    int* AdPrCoLi0 = malloc(nbtng*sizeof(int));
    float* Matrice0 = malloc((nbtng+NbCoef)*sizeof(float)); 
    int* NumCol0 = malloc(NbCoef*sizeof(int)); 

//passage SMD->SMO
    dSMDaSMO(&nbtng, NbCoef, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, NumDLDir, ValDLDir, AdPrCoLi0, NumCol0, Matrice0, SecMemb0);

//affichage système assemblé en SMO
if (affichage>=2){
    affsmo_(&nbtng, AdPrCoLi0, NumCol0, Matrice0, SecMemb0);
}

//déclaration des variables relatives au stockage profil (nbtng == Nblign)
    NbCoef = AdPrCoLi0[nbtng]-1;
    int LongProfil =  dSMOaLongPR_nous(nbtng,AdPrCoLi0,NumCol0,Matrice0);
    int* Profil = malloc(nbtng*sizeof(int));
    float* MatProf = malloc(LongProfil*sizeof(float)); 

//passage SMO->Profile 
    dSMOaPR_nous(nbtng, AdPrCoLi0,NumCol0, Matrice0, LongProfil, Profil, MatProf);
   
//affichage du système en profil
const int a = 1;
if(affichage>=3){ 
    impmpr_(&a,&nbtng, Profil, MatProf, &MatProf[nbtng]);
}


//libération de la mémoire
    free(numRefD0); free(numRefD1); free(numRefF1);
    freetab(coord); freetab(ngnel); freetab(nRefAr);

    free(SecMembre); free(Matrice); 
    free(NumDLDir); free(ValDLDir);
    free(AdPrCoefLi); free(AdSuccLi); free(NumCol); 

    free(Profil); free(MatProf);
}