/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 01/02/2026
--------------------------------------------------------------------------------
*/

#include "../../include/headerTP1.h"

void lecture_fichier_maillage(float* a,float* b, float* c,float* d, int* n1, int* n2, int* t){
    FILE *pFile;
 
    //lecture du fichier qui set up le cadre
    pFile = fopen("input_maillage.txt", "r");
    if(pFile == NULL){
        printf("Erreur d'ouverture du fichier pour lecture.\n");
        printf("Veuillez écrire un fichier de maillage.\n");
        printf("Nom supporté : input_maillage.txt .\n");
        exit(EXIT_FAILURE);
    }

    fscanf(pFile,"%f %f %f %f",a,b,c,d);
	fscanf(pFile,"%d %d",n1,n2);
	fscanf(pFile,"%d",t);
    fclose(pFile);
}

void nombre_points(int n1, int n2, int* n, FILE* pFile){
    *n = n1*n2;
    fprintf(pFile, "%d\n",*n);
}

void coordonees_points(float a, float b, float c, float d, float* h1, float* h2, int n1, int n2, FILE* pFile){
    float x,y,r,qot;

    *h1 = (b-a)/(n1-1); //pas sur côté 1
    *h2 = (d-c)/(n2-1); //pas sur côté 2
    int n = n1*n2;

    //calcul coordonnées en utilisant la division euclidienne 
    for(int i=0; i < n;i++){
		qot = i/n1;  r = i%n1;

		x = a+r*(*h1); y = c+qot*(*h2);

		fprintf(pFile,"%f %f\n",x,y);
	}
}

void ecriture_mtpq(int* m, int t, int* p, int* q, int n1, int n2, FILE* pFile){
    if(t==1){//quadrangles
        *p = 4; *m = (n1-1)*(n2-1);  *q = 4;
    }
    else if(t==2){//triangles
        *p = 3; *m = 2*(n1-1)*(n2-1); *q = 3;
    }
    fprintf(pFile,"%d %d %d %d\n",*m,t,*p,*q);
}

void etiqAr(int typel, int n1, int n2, int nrefdom, int* nrefcot, int nbtel, int nbaret, int** nRefAr){
    //défault sur tous les r : nrefdom de l'intérieur du domaine
    for(int i=0; i<nbtel; i++){
        for(int j=0; j<nbaret; j++){
            nRefAr[i][j] = nrefdom;
        }

    }

    //balayages des côtés pour assignation différentes 
    if(typel==1){ //quadrangles
        for(int i=0;i<n1-1; i++){ //balayage horizontal
            nRefAr[i][3] = nrefcot[0]; //cas en bas
            nRefAr[(nbtel-1)-i][1] = nrefcot[2]; //cas en haut
        }
        for(int i=0;i<n2-1; i++){ //balayage vertical
            nRefAr[i*(n1-1)][2] = nrefcot[3]; //cas à gauche
            nRefAr[i*(n1-1) + (n1-2)][0] = nrefcot[1]; //cas à droite
        }
    }

    else if(typel==2){ //triangles
        for(int i=0;i<n1-1; i++){ //balayage horizontal
            nRefAr[2*i][2] = nrefcot[0]; //cas en bas
            nRefAr[(nbtel-1)-2*i][2] = nrefcot[2]; //cas en haut
        }
        for(int i=0;i<n2-1; i++){ //balayage vertical
            nRefAr[2*i*(n1-1)][1] = nrefcot[3]; //cas à gauche
            nRefAr[2*i*(n1-1) + 2*(n1-2) +1][1] = nrefcot[1]; //cas à droite
        }
    }
    
}

void calc_s_ecrire_s_et_r(int t, int n1, int n2, int** nRefAr, FILE* pFile){

    int* s_ref = (int*)malloc(6*sizeof(int));
    int* s = (int*)malloc(6*sizeof(int));
    //on créé un quadrangles de référence avec des numéros globaux en fonction de n1.
    //on va calculer puis écrire les nums globaux des translations de cette ref.

    //dans le le vecteur s_ref et s
    //  numéros globaux de K1 : 0 -> 3 
    //  4->5 pas utilisés donc pas initialisés (pas besoin) 

    if(t==1){ //t = 1 : quadrangles
        s_ref[0] = 2; s_ref[1] = n1+2; //quadrangle K1
        s_ref[2] = n1+1; s_ref[3] = 1;
        int nbcarré=0;
        for(int j=0; j< n2-1; j++){
            for(int i=0; i< n1-1; i++){
                //translation des 4 composantes globales du quadrangles de ref
                for(int indice = 0 ; indice <4 ; indice ++){
                    s[indice] = s_ref[indice] + i + j*n1;
                    fprintf(pFile,"%d ",s[indice]);
                }
                for(int indice = 0 ; indice <4 ; indice ++){
                    fprintf(pFile,"%d ",nRefAr[nbcarré][indice]);
                }
                fprintf(pFile,"\n");
                nbcarré+=1;
            }
        } 
    }

    //on créé deux triangles de référence avec des numéros globaux en fonction de n1.
    //on va calculer puis écrire les nums globaux des translations de ces refs.

    //dans le le vecteur s_ref 
    //numéros globaux de K1 : 0 -> 2 ; numéros globaux de K2 : 3 -> 5
    //dans le le vecteur s
    //numéros globaux de K_impaire : 0 -> 2 ; numéros globaux de K_paire : 3 -> 5
    
    else if(t==2){ //t = 2 : triangles
        s_ref[0] = 2; s_ref[1] = n1+1; s_ref[2] = 1;   //triangle K1 (gauche)
        s_ref[3] = n1+1; s_ref[4] = 2; s_ref[5] = n1+2;//triangle K2 (droite)
        int nbtriangle = 0;
        for(int j=0; j<n2-1; j++){
            for(int i=0; i<n1-1; i++){

                //translation des 3 composantes globales du triangle de ref gauche
                for(int indice = 0 ; indice < 3 ; indice ++){
                    s[indice] = s_ref[indice] + i + j*n1;
                    fprintf(pFile,"%d ", s[indice]);
                }

                for(int indice = 0 ; indice <3 ; indice ++){
                    fprintf(pFile,"%d ",nRefAr[nbtriangle][indice]);
                }
                nbtriangle+=1;
                fprintf(pFile,"\n");

                //translation des 3 composantes globales du triangle de ref droit
                for(int indice = 3 ; indice < 6 ; indice ++){
                    s[indice] = s_ref[indice] + i + j*n1;
                    fprintf(pFile,"%d ", s[indice]);
                }

                for(int indice = 0 ; indice <3 ; indice ++){
                    fprintf(pFile,"%d ",nRefAr[nbtriangle][indice]);
                }
                nbtriangle+=1;

                fprintf(pFile,"\n");
            }
        }
    }
    free(s_ref); free(s);
}

