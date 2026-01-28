#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/headers.h"
#include "../include/errhandle.h"


//Fonction qui check le format du fichier de maillage
//Affiche au terminal les erreurs si il y en a et stop le processus
//Affiche le format supporté à écrire dans le fichier de maillage
//Entrée : bornes a,b,c,d du domaine
//         nombres n1 et n2 de points sur les côtés 1 et 2 resp. 
//         type t d'élément
//
//Sortie : 0 si format conforme
//         1 si une erreur a été trouvée (minimum)
//
//Appelle la fonction d'affichage d'erreur spécifique à chaque erreur de format sur les variables.
int fichier_maillage_format_check(float* a, float* b, float* c, float* d, int* n1, int* n2, int* t){
    int check = 0;

    if(*t < 1 || *t > 2){
        check = 1;
        t_pas_conforme(*t);
    }

    //ajouter conditions de format sur a,b,c,d

    if(*n1 < 2 || *n2 <2){
        check = 1;
        n1_n2_pas_conforme(*n1,*n2);
    }

    return(check);
}

void t_pas_conforme(int t){
    printf("\n");
    printf("ERROR \n");
    printf("/! Le fichier de maillage n'est pas conforme. \n");
    printf("    t = %d ne correspond à aucun type d'élément supporté. \n", t);
    printf("    Les types supportés sont : \n");
    printf("        - quadrangles : t = 1 \n");
    printf("        - triangles : t = 2 \n");
}

void n1_n2_pas_conforme(int n1,int n2){
    printf("\n");
    printf("ERROR \n");
    printf("/! Le fichier de maillage n'est pas conforme.\n");
    printf("    n1=%d, n2=%d ne peuvent pas générer de maillage.\n", n1,n2);
    printf("    n1 et n2 doivent être supérieur ou égale à 2.\n");
    printf("\n");
}