#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/headers.h"
#include "include/errhandle.h"

//se mettre dans le dossier et entrer dans le terminal : 

void main() {

    float a,b,c,d; int n1,n2,t;
    lecture_fichier_maillage(&a,&b,&c,&d,&n1,&n2,&t);

    int format = fichier_maillage_format_check(&a,&b,&c,&d,&n1,&n2,&t);

    if(format==1) {
        printf("/! Veillez à écrire le fichier de maillage dans le format supporté.\n");
        printf("\n");
        exit(EXIT_FAILURE);
    }

    FILE* pFile;
    pFile = fopen("cad.txt", "w");
    if(pFile == NULL){
        printf("Erreur d'ouverture du fichier pour écriture\n");
        exit(EXIT_FAILURE);
    }

    //calcul et écriture de n
    int n;
    nombre_points(n1,n2,&n,pFile);

    //calcul et écriture des coordonnées 
    float h1,h2;
    coordonees_points(a,b,c,d,&h1,&h2,n1,n2,pFile);

    int p,m,q;
    ecriture_mtpq(&m,t,&p,&q,n1,n2,pFile);


    //pour les tests
    int nrefdom = 0;
    int* nrefcot = malloc(4*sizeof(int));
    for(int i=0;i<4;i++) {
        nrefcot[i]=(i+1);
        //printf("nref coté [%d] = %d \n",i+1,nrefcot[i]);
    }
    //pour les tests

    //peut être une fonction à elle-même
    int* nRefArLoc = malloc(m*q*sizeof(int));
    int** nRefAr = malloc(m*sizeof(int*));
    for(int i=0; i<m; i++) nRefAr[i]= &nRefArLoc[i*q];

    etiqAr(t,n1,n2,nrefdom,nrefcot,m,q,nRefAr);

    //calcul et écriture des s_i (numéros globaux des noeuds par élément)
    // + écriture des r_i (numéros de référence des arêtes de chaque élément)
    calc_s_ecrire_s_et_r(t,n1,n2,nRefAr,pFile);
    
	fclose(pFile);
    free(nrefcot);
    free(nRefAr);free(nRefArLoc);
}
