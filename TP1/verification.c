/*
--------------------------------------------------------------------------------
    Damien MALETTE, Ehouarn DONNIOU, Dora PAPAI

    Ecrit le 01/02/2026
--------------------------------------------------------------------------------
*/

#include "include/headers.h"
#include "include/errhandle.h"

void main(){
    char* ficmai = "output_maillage.txt";
    float** pcoord;
    int** pngnel; 
    int** pnRefAr;
    int ptypel, pnbtng, pnbtel, pnbneel, pnbaret;

    int lecfima(ficmai,&ptypel,&pnbtng,&pcoord,&pnbtel,&pngnel, &pnbneel, &pnbaret, &pnRefAr);
    int lecture = lecfima(ficmai,&ptypel,&pnbtng,&pcoord,&pnbtel,&pngnel, &pnbneel, &pnbaret, &pnRefAr);

    //check de sortie de lecture
    if(lecture == 1)exit(EXIT_FAILURE);

    FILE* pFile;
    pFile = fopen("verif.txt", "w");
    if(pFile == NULL){
        printf("Erreur d'ouverture du fichier pour écriture\n");
        exit(EXIT_FAILURE);
    }

    fprintf(pFile,"%d\n",pnbtng);

    for(int i=0; i<pnbtng;i++){
        fprintf(pFile,"%f %f\n",pcoord[i][0],pcoord[i][1]);
    }

    fprintf(pFile,"%d %d %d %d\n",pnbtel, ptypel, pnbneel, pnbaret);
    for(int i=0; i<pnbtel;i++){
        for(int j=0;j<pnbneel;j++){
            fprintf(pFile,"%d",pngnel[i][j]);

    fprintf(pFile,"%d %d %d %d\n",pnbtel, ptypel, pnbneel, pnbaret);
    for(int i=0; i<pnbtel;i++){
        for(int j=0;j<pnbneel;j++){
            fprintf(pFile,"%d ",pngnel[i][j]);
        }
        for(int j=0;j<pnbaret;j++){
            fprintf(pFile,"%d",pnRefAr[i][j]);
        for(int j=0;j<pnbaret;j++){
            fprintf(pFile,"%d ",pnRefAr[i][j]);
        }
        fprintf(pFile,"\n");
    }

    freetab(*pcoord);
    freetab(*pngnel);
    freetab(*pnRefAr);

    freetab(pcoord);
    freetab(pngnel);
    freetab(pnRefAr);
}