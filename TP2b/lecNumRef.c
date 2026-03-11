/*
--------------------------------------------------------------------------------
    Damien MALETTE, Ehouarn DONNIOU, Dora PAPAI

    Ecrit le 11/03/2026
--------------------------------------------------------------------------------
*/

#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"

int lecNumRef(char* ficmai, int* nbrefdm,int* nbRefD0, int* nbRefD1, int* nbRefF1, int* numRefD0, int* numRefD1, int* numRefF1){
    FILE *pFile;
    pFile = fopen(ficmai, "r");
    if(pFile == NULL){
        printf("Erreur d ouverture du fichier pour lecture\n");
        return 1;
    }
    //numero de reference du domaine
    fscanf(pFile,"%d",nbrefdm);
    //nombre de numeros de reference Dirichlet homogene + tableau des numeros de reference Dirichlet homogene
    fscanf(pFile,"%d",nbRefD0);
    numRefD0=calloc(nbRefD0,sizeof(int));
    for(int i=0;i<nbRefD0;i++){
        fscanf(pFile,"%d",nbRefD0[i]);
    }
    //nombre de numeros de reference Dirichlet non homogene + tableau des numeros de reference Dirichlet non homogene
    fscanf(pFile,"%d",nbRefD1);
    numRefD1=calloc(nbRefD1,sizeof(int));
    for(int i=0;i<nbRefD1;i++){
        fscanf(pFile,"%d",nbRefD1[i]);
    }
    //nombre de numeros de reference Neumann + tableau des numeros de reference Neumann
    fscanf(pFile,"%d",nbRefF1);
    numRefD0=calloc(nbRefF1,sizeof(int));
    for(int i=0;i<nbRefF1;i++){
        fscanf(pFile,"%d",nbRefF1[i]);
    }

    return 0;
}