#include "include/headers.h"
#include "include/errhandle.h"

void main(){
    char *ficmai = "cad.txt";
    float **pcoord;
    int **pngnel, **pnRefAr;
    int  ptypel, pnbtng, pnbtel, pnbneel, pnbaret;

    int lecfima(*ficmai,&ptypel,&pnbtng,&pcoord,&pnbtel,&pngnel, &pnbneel, int *pnbaret, int ***pnRefAr);

    FILE* pFile;
    pFile = fopen("verif.txt", "w");
    if(pFile == NULL){
        printf("Erreur d'ouverture du fichier pour écriture\n");
    }
    fprintf(pFile,"%d\n",pnbtng);
    for(int i=0; i<pnbtng;i++){
        fprintf(pFile,"%f %f\n",pcoord[0][i],pcoord[1][i]);
    }
    for(int i=0; i<*pnbtel;i++){
        for(int j=0;j<*pnbneel;j++){
            fprintf(pFile,"%d",pngel[i][j]);
        }
        for(int j=0;j<*pnbaret;j++){
            fprintf(pFile,"%d",pnRefAr[i][j]);
        }
        fpro
    }
}