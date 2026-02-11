/*
--------------------------------------------------------------------------------
    Damien MALETTE, Ehouarn DONNIOU, Dora PAPAI

    Ecrit le 01/02/2026
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/headerTP1.h"

int lecfima(char* ficmai, int *ptypel, int *pnbtng, float***pcoord, int *pnbtel, int ***pngnel, int *pnbneel, int *pnbaret, int ***pnRefAr){
    FILE *pFile;
    pFile = fopen(ficmai, "r");
    if(pFile == NULL){
        printf("Erreur d ouverture du fichier pour lecture\n");
        return 1;
    }

    // Lecture de n
    fscanf(pFile,"%d",pnbtng);
    //Allouer le tableau pour stocker les coordonnees de dimension n x 2
    *pcoord=alloctab(2,*pnbtng);
    //Lexture des coordonnees
    for(int i=0;i<*pnbtng;i++){
        fscanf(pFile,"%f %f",&(*pcoord)[0][i],&(*pcoord)[1][i]);
       // printf("%f %f \n",(*pcoord)[0][i],(*pcoord)[1][i]);
    }
    //Lecture de pnbtel=m, ptypel=t, pnbneel=p, pnbaret=q
    fscanf(pFile,"%d %d %d %d",pnbtel,ptypel,pnbneel,pnbaret);
    //Allouer les tableaux pour pngnel de dimension mxp et pour pnRefAr de dimension mxq
    *pngnel=alloctabint(*pnbtel,*pnbneel);
    *pnRefAr=alloctabint(*pnbtel,*pnbaret);
    //Lecture et remplissage des tableaux pngnel et pnRefAr
    for(int i=0; i<*pnbtel;i++){
        for(int j=0;j<*pnbneel;j++){
            fscanf(pFile,"%d",&(*pngnel)[i][j]);
        }
        for(int j=0;j<*pnbaret;j++){
            fscanf(pFile,"%d",&(*pnRefAr)[i][j]);
        }
        
    }
    return 0;
}