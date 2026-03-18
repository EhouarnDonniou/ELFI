/*
--------------------------------------------------------------------------------
    Damien MALETTE, Ehouarn DONNIOU, Dora PAPAI

    Ecrit le 11/03/2026
--------------------------------------------------------------------------------
*/
//gcc Test_lecNumRef.c lecNumRef.c functions/fonctions_utilitaires/gestion_tab.c
#include "include/headerTP1.h"
#include "include/headerTP2a.h"
#include "include/headerTP2b.h"
#include "include/utilitaires.h"

void main(){  
  char* ficmai = "NUMREF.Test";
  int nbRefdm,nbRefD0,nbRefD1,nbRefF1;
  int* numRefD0;
  int* numRefD1;
  int* numRefF1;

  lecNumRef(ficmai,&nbRefdm,&nbRefD0,&nbRefD1,&nbRefF1,&numRefD0,&numRefD1,&numRefF1);
  printf("nbrefdm = %d \n",nbRefdm);

  printf("nbrefD0 = %d \nnumRefD0=[ ",nbRefD0);
  for(int i=0;i<nbRefD0;i++){
    printf("%d ",numRefD0[i]);
  }
  printf("]\n");

  printf("nbrefD1 = %d \nnumRefD1=[ ",nbRefD1);
  for(int i=0;i<nbRefD1;i++){
    printf("%d ",numRefD1[i]);
  }
  printf("]\n");

  printf("nbrefF1 = %d \nnumRefF1=[ ",nbRefF1);
  for(int i=0;i<nbRefF1;i++){
    printf("%d ",numRefF1[i]);
  }  
  printf("]\n");
}