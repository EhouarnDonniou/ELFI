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

int nucas;

void main(){
//déclaration-init pour la lecture de fichiers
    char buffer1[100];
    char buffer2[100];
    char* ficRef;
    char* ficmai;

    int IMPFCH;
    int domaine; 
    int type;

//demande d'interraction utilisateur

    //input num_domaine
    printf("\nEntrez le numéro du domaine :\n");
    scanf("%d", &domaine); 
    if(domaine==1 || domaine==2){
        printf("Domaine %d.\n",domaine);
    }
    else{
        printf("Domaine non supporté, veuillez réessayer.");
        EXIT_FAILURE;
    }

    //input nucas
    printf("\nEntrez le numéros du cas voulu (1,2 ou 3) :\n");
    scanf("%d", &nucas); 
    switch(nucas){
        case(1):
        case(2):
            ficRef = "input/NUMREF_%d"; break;
        case(3):
            ficRef = "input/NUMREF_%d_%d"; break;
        default : printf("Cas non supporté, veuillez réessayer.");EXIT_FAILURE;
    }
    if(nucas==3) sprintf(buffer2, ficRef, nucas,domaine);
    else sprintf(buffer2, ficRef, nucas);

    //input type_element
    printf("\nEntrez le type d'élément :\n");
    printf(" - 1 : quadrangles\n - 2 : triangles\n");
    scanf("%d", &type); 
    if(type ==1){
            ficmai = "input/maillage/d%dq1_%d";
    }
    if(type ==2){
            ficmai = "input/maillage/d%dt1_%d";
    }
    else{
        printf("Type non supporté, veuillez réessayer.");
        EXIT_FAILURE;
    }

    //input affichage/fichier
    printf("\nAffichage des résultats finaux en fichier ?\n");
    printf(" - positif : dans un fichier\n - négatif : dans le terminal\n");
    scanf("%d", &IMPFCH); 
    
    
//boucler les calculs sur les valeurs de h (avec les fichiers différents et tout)
printf("Lecture du fichier %s\n",buffer2);
    for(int i=2;i<=64;i=i*2){
        sprintf(buffer1, ficmai, domaine,i);
        printf("Lecture du fichier %s\n",buffer1);
        
        
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
    int check = lecfima(buffer1,&typeEl,&nbtng,&coord,&nbtel,&ngnel,&nbneel,&nbaret,&nRefAr);
    
    lecNumRef(buffer2,&nRefDom,&nbRefD0,&nbRefD1,&nbRefF1,&numRefD0,&numRefD1,&numRefF1);  

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
    //impmpr_(&IMPFCH, &nbtng, Profil, MatProf, MatProf+nbtng);
    

//Calcul de la solution éléments finis 
    float eps = 1.0e-10; //seuil de singularité de 
    float* MatLow = malloc(LongProfil*sizeof(float)); //matrice triangulaire l de A = LLt
    float* U = malloc(nbtng*sizeof(float)); //vecteur de solution calculée 
    float* Y = malloc(nbtng*sizeof(float));
    ltlpr_(&nbtng,Profil,MatProf,MatProf+nbtng,&eps,MatLow,MatLow+nbtng); //facto LLt
    rsprl_(&nbtng,Profil,MatLow,MatLow+nbtng,SecMemb0,Y); //descente
    rspru_(&nbtng,Profil,MatLow,MatLow+nbtng,Y,U); //remontée



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
}