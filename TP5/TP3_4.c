/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 02/04/2026
--------------------------------------------------------------------------------
*/


//pour compiler : bash compil.sh dans le dossier actuel

#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/headerTP3_4.h"
#include "include/forfun.h"
#include "include/utilitaires.h"

void main(){
//déclaration-init pour la lecture de fichiers
    char* ficmai;
    printf("\nDonner le nom du fichier de maillage : ");
    scanf("%s", ficmai); 
    char* ficRef = "input/NUMREF.Test";
    printf("Lecture du fichier %s\n\n",ficRef);

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

//declaration des variables relatives au stockage morse ordonné
    float* SecMemb0 = malloc(nbtng*sizeof(float));
    int* AdPrCoLi0 = malloc(nbtng*sizeof(int));
    float* Matrice0 = malloc((nbtng+NbCoef)*sizeof(float)); 
    int* NumCol0 = malloc(NbCoef*sizeof(int));

//assemblage du système linéaire (matrices élémentaires, assemblage SMO, passage SMO->SMD)
    Assemblage(nRefDom,nbRefD0,numRefD0,nbRefD1,numRefD1,nbRefF1,numRefF1,
            coord ,ngnel ,nRefAr ,typeEl ,nbtng ,nbtel ,nbneel ,nbaret ,
            nbtng ,NbCoef ,SecMembre ,NumDLDir ,ValDLDir ,AdPrCoefLi ,Matrice ,NumCol ,AdSuccLi, 
            SecMemb0 , AdPrCoLi0 , Matrice0 ,NumCol0);
    
//affichage système assemblé en SMD
    affsmd_(&nbtng, AdPrCoefLi, NumCol, AdSuccLi, Matrice, SecMembre, NumDLDir, ValDLDir);

//affichage système assemblé en SMO
    affsmo_(&nbtng, AdPrCoLi0, NumCol0, Matrice0, SecMemb0);

//libération de la mémoire
    free(numRefD0); free(numRefD1); free(numRefF1);
    freetab(coord); freetab(ngnel); freetab(nRefAr);

    free(SecMembre); free(Matrice); 
    free(NumDLDir); free(ValDLDir);
    free(AdPrCoefLi); free(AdSuccLi); free(NumCol); 
}