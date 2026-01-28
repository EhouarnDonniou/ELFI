#include <stdio.h>
#include <stdlib.h>

//fonction de lecture de fichier_maillage.txt
void lecture_fichier_maillage(float*, float*, float*, float*, int*, int*, int*);

/* Fonctions de calculs + écriture dans cad.txt */
//calcul et écriture de n nombre de points 
void nombre_points(int, int, int*, FILE*);
//calcul des pas, des coordonées de chaque point et écriture des coordonnées
void coordonees_points(float, float, float, float, float*, float*, int, int, FILE*);
//calcul et écriture de m, t, p, q en fonction de t et n1, n2
void ecriture_mtpq(int*, int, int*, int*, int, int, FILE*);
//calcul de s et écriture des s et des r pour chaque élément
void calc_s_ecrire_s_et_r(int, int, int, int**, FILE*);
//étiquetage des arêtes
void etiqAr(int, int ,int, int, int*, int, int, int**);

float** alloctab(int, int);
void freetab(void*); 

int lecfima(char*, int*, int*, float***, int*, int***, int*, int*, int***);