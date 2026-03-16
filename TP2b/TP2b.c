#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"

void main(){
    char* ficmai = "car1x1q_4";
    float** coord;
    int** ngnel; 
    int** nRefAr;
    int typeEl, nbtng, nbtel, nbneel, nbaret;
    int nRefDom, nbRefD0, nbRefD1, nbRefF1;
    int* numRefD0;
    int* numRefD1;
    int* numRefF1;
    int* nrefArEl;
    int  check = lecfima(ficmai,&typeEl,&nbtng,&coord,&nbtel,&ngnel,&nbneel,&nbaret,&nRefAr);
    
    //Allocation
    float** MatElem=alloctab(nbneel,nbneel);
    float* SMbrElem=calloc(nbneel,sizeof(float));
    int* NuDElem=calloc(nbneel,sizeof(int));
    float* uDElem=calloc(nbneel,sizeof(float));
    float** coorEl=alloctab(nbneel,2);

    //Boucle sur les éléments K
    for(int k=0;k<2;k++){
        printf("---------Element actuel K = %d \n", k+1);
        //Initialisation à 0 de MatElem, SMbrElem, NuDElem et uDElem
        for(int i=0; i<nbneel ; i++){
            SMbrElem[i]=0;
            NuDElem[i]=0;
            uDElem[i]=0;
            for(int j=0; j<nbneel; j++){
            MatElem[i][j]=0;
            }
        }

        for(int i=0;i<nbtel;i++){
            for(int j=0;j<nbneel;j++){
                printf("num global pt = %d\n",ngnel[j][i]);
            }
            printf("---\n");
        }

        selectPts(nbneel,ngnel[k],coord,coorEl);

        for(int i=0; i<nbneel ; i++){
           printf("(%f, %f)\n", coorEl[i][0],coorEl[i][1]);
        }

        cal1Elem(nRefDom, nbRefD0, numRefD0, nbRefD1, numRefD1, nbRefF1, numRefF1, 
                   typeEl, nbneel, coorEl, nbaret, nrefArEl,
                   MatElem, SMbrElem, NuDElem, uDElem);

        //impCalEl(k, typeEl, nbneel, MatElem, SMbrElem, NuDElem, uDElem) ;
    }
}