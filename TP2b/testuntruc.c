#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"
void main(){
    char* ficmai = "car1x1q_4";
    int typeEl;
    int nbtng;
    float** coord;
    int nbtel;
    int** ngnel; 
    int nbneel;
    int nbaret;
    int** nRefAr;
    int check = lecfima(ficmai,&typeEl,&nbtng,&coord,&nbtel,&ngnel, &nbneel, &nbaret, &nRefAr);
    printf("%d \n",check);
}