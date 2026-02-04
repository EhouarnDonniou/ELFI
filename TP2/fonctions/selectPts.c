/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 04/02/2026
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/headers.h"


//Associe le num global num[] de nb points à leurs coordonées coorSel[]
// en passant par la "liste" de toutes le coordonnées coorEns (ordonnée croissant par num globale)
//
//entrée : int nb, nombre de points séléctionnés
//         int num[], liste des numéros globaux de chaque point
//         float* coorEns[], pointeur vers les coordonnées(pointeur 1x2) des points
//                           rangés par ordre croissant de la numérotation globale
//
//sortie : float* coorSel[], pointeur vers les coordonnées(pointeur 1x2) des points séléctionnés
//                           pointe aux mêmes endroits de la mémoire que coorEns, 
//                           pour seulement les points séléctionnés associés par leur numéro global.
void selectPts(int nb, int num[], float* coorEns[], float* coorSel[]){
    for(int i=0; i<nb;i++){
        *coorSel[i] = *coorEns[num[i]-1]; //-1, les num globaux sont >=1
    }
}