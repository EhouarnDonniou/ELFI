#include "include/headers.h"
#include "include/errhandle.h"

void main(){
    char* ficmai = "cad.txt";
    float** pcoord;
    int** pngnel;
    int** pnRefAr;
    int  typel, nbtng, nbtel, nbneel, nbaret;

    int truc = lecfima(ficmai, &typel, &nbtng, &pcoord, &nbtel, &pngnel, &nbneel, &nbaret, &pnRefAr);

    FILE* pFile;
    pFile = fopen("verif.txt", "w");
    if(pFile == NULL){
        printf("Erreur d'ouverture du fichier pour écriture\n");
        exit(EXIT_FAILURE);
    }
    fprintf(pFile,"%d\n",nbtng);
    for(int i=0; i<nbtng;i++){
        fprintf(pFile,"%f %f\n",pcoord[0][i],pcoord[1][i]);
    }
    for(int i=0; i<nbtel;i++){
        for(int j=0;j<nbneel;j++){
            fprintf(pFile,"%d",pngnel[i][j]);
        }
        for(int j=0;j<nbaret;j++){
            fprintf(pFile,"%d",pnRefAr[i][j]);
        }
    }
}