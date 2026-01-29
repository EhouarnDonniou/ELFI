#include <stdio.h>
#include <stdlib.h>
#include "../include/headers.h"

int lecfima(char* ficmai, int* ptypel, int* pnbtng, float*** pcoord, int* pnbtel, int*** pngnel, int* pnbneel, int* pnbaret, int*** pnRefAr){
    FILE *pFile;
    pFile = fopen(ficmai, "r");
    if(pFile == NULL){
        printf("Erreur d ouverture du fichier\n");
    return 1;
    }

    // Lecture de n
    fscanf(pFile,"%d",pnbtng);
    //Allouer le tableau pour stocker les coordonnees de dimension n x 2
    float **pcoord1=alloctab(*pnbtng,2);
    //Lexture des coordonnees
    for(int i=0;i<*pnbtng;i++){
        fscanf(pFile,"%f %f",&(*pcoord)[0][i],&(*pcoord)[1][i]);
    }
    //Lecture de pnbtel=m, ptypel=t, pnbneel=p, pnbaret=q
    fscanf(pFile,"%d %d %d %d",pnbtel,ptypel,pnbneel,pnbaret);

    //Allouer les tableaux pour pngnel de dimension mxp et pour pnRefAr de dimension mxq
    int **pngel1=alloctabint(*pnbtel,*pnbneel);
    int **pnRefAr1=alloctabint(*pnbtel,*pnbaret);

    //Lecture et remplissage des tableaux pngnel et pnRefAr
    for(int i=0; i<*pnbtel;i++){
        for(int j=0;j<*pnbneel;j++){
            fscanf(pFile,"%d",pngel1[i][j]);
        }
        for(int j=0;j<*pnbaret;j++){
            fscanf(pFile,"%d",&(*pnRefAr)[i][j]);
        }
        
    }

    ***pcoord = **pcoord1;
    ***pngel1 = **pcoord1;
    ***pnRefAr= **pnRefAr1;
    //Liberes les tableaux
    freetab(*pcoord);
    freetab(*pngel1);
    freetab(*pnRefAr);
    return 0;
}