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

int nucas=1;

void main(){

//boucler les calculs sur les valeurs de h (avec les fichiers différents et tout)

//déclaration-init pour la lecture de fichiers
    char* ficmai = "input/maillage/d1t1_64";
    printf("Lecture du fichier %s\n\n",ficmai);
    char* ficRef = "input/NUMREF_1";
    printf("Lecture du fichier %s\n\n",ficRef);
    int affichage; int IMPFCH;
    printf("Voulez-vous afficher les résultats ?\n");
    printf(" Aucun affichage : 0\n Affichage SMD : 1\n Affichage SMD-SMO : 2\n Affichage SMD-SMO-Profile : 3\n");
    scanf("%d", &affichage); 
    printf("Affichage des résultats finaux en fichier ?\n");
    printf(" positif : dans un fichier\n  négatif : dans le terminal\n");
    scanf("%d", &IMPFCH); 

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
    //
    // affsmd_(&nbtng, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, NumDLDir, ValDLDir);
    // 


//declaration des variables relatives au stockage morse ordonné
    NbCoef = AdPrCoefLi[nbtng-1];
    float* SecMemb0 = malloc(nbtng*sizeof(float));
    int* AdPrCoLi0 = malloc(nbtng*sizeof(int));
    float* Matrice0 = malloc((nbtng+NbCoef)*sizeof(float)); 
    int* NumCol0 = malloc(NbCoef*sizeof(int)); 

//passage SMD->SMO
    dSMDaSMO(&nbtng, NbCoef, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, NumDLDir, ValDLDir, AdPrCoLi0, NumCol0, Matrice0, SecMemb0);

//affichage système assemblé en SMO
    // 
    // affsmo_(&nbtng, AdPrCoLi0, NumCol0, Matrice0, SecMemb0);
    // 

//déclaration des variables relatives au stockage profil (nbtng == Nblign)
    NbCoef = AdPrCoLi0[nbtng]-1;
    int LongProfil =  dSMOaLongPR(nbtng,AdPrCoLi0,NumCol0,Matrice0);
    int* Profil = malloc(nbtng*sizeof(int));
    float* MatProf = malloc(LongProfil*sizeof(float)); 

//passage SMO->Profile 
    dSMOaPR(nbtng, AdPrCoLi0,NumCol0, Matrice0, LongProfil, Profil, MatProf);
   
//affichage du système en profil
    // 
    // impmpr_(&IMPFCH, &nbtng, Profil, MatProf, MatProf+nbtng);
    //

//Calcul de la solution éléments finis 
    float eps = 1.0e-10; //seuil de singularité de 
    float* MatLow = malloc(LongProfil*sizeof(float)); //matrice triangulaire l de A = LLt
    float* U = malloc(nbtng*sizeof(float)); //vecteur de solution calculée 
    ltlpr_(&nbtng,Profil,MatProf,MatProf+nbtng,&eps,MatLow,MatLow+nbtng); //facto LLt
    rsprl_(&nbtng,Profil,MatLow,MatLow+nbtng,SecMemb0,U); //descente
    rspru_(&nbtng,Profil,MatLow,MatLow+nbtng,SecMemb0,U); //remontée


//Tableau de UEX(I)
    float* UEX = malloc(nbtng*sizeof(float)); //vecteur de solution calculée 
    CalSol(nbtng, coord, UEX); //calcul de la solution exacte sur les points du domaine

//affichage du système en profil
    affsol_(&nbtng,*coord,U,UEX,&IMPFCH);


//Libération de la mémoire
    free(numRefD0); free(numRefD1); free(numRefF1);
    freetab(coord); freetab(ngnel); freetab(nRefAr);

    free(SecMembre); free(Matrice); 
    free(NumDLDir); free(ValDLDir);
    free(AdPrCoefLi); free(AdSuccLi); free(NumCol); 

    free(Profil); free(MatProf);
    free(MatLow); free(U); free(UEX);
}