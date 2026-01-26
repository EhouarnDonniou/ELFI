#include <stdio.h>
#include <stdlib.h>
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
    
    //ajouter conditions de format sur a,b,c,d ; n1,n2
    //et créer les fonctions d'affichage de l'erreur

    if(*t < 1 || *t > 2){
        check = 1;
        t_pas_conforme(t);
    }
    return(check);
}

void t_pas_conforme(int* t){
    printf("\n");
    printf("ERROR \n");
    printf("/! Le fichier de maillage n'est pas conforme. \n");
    printf("    t = %d ne correspond à aucun type d'élément supporté. \n", *t);
    printf("    Les types supportés sont : \n");
    printf("        - quadrangles : t = 1 \n");
    printf("        - triangles : t = 2 \n");
    printf("/! Veillez à écrire le fichier de maillage dans le format supporté.\n");
    printf("\n");
}