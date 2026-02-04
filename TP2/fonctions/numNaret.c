/*
--------------------------------------------------------------------------------
    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI

    Ecrit le 04/02/2026
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/headers.h"

// attention à ne pas appliquer aux segments (t=3)

//prend le numéro local d'une arête et ressort le couple de numéros locaux des sommets associés
// en fonction du type de l'élément et ordonné en sens anti-horaire (numérotation locale de ref)
//entrée : int* numaret, pointeur scalaire, num local d'une arête
//         int t, type de l'élément (t==1 -> quadrangle, t==2 -> triangle)
//sortie : int numsommet[], pointeur 2x1 où est placé le couple (_,_), sommets de l'arête en entrée
void numNaret(int* numaret, int numsommets[], int t){
    switch(*numaret){
        case(1): 
        //num-arête == 1 -> sommets : (1,2)
            numsommets[0]=1;
            numsommets[1]=2;
            break;
        case(2):
        //num-arête == 2 -> sommets : (2,3)
            numsommets[0]=2;
            numsommets[1]=3;
            break;
        case(3):
        //num-arête == 3 
            if(t==1){ //quadrangle
                //-> sommets : (3,4)
                numsommets[0]=3;
                numsommets[1]=4;
            }
            if(t==2){ //triangle
                //-> sommets : (3,1)
                numsommets[0]=3;
                numsommets[1]=1;
            }
            break;
        case(4): //uniquement pour le quadrangle
        //num-arête == 4 -> sommets : (4,1)
            numsommets[0]=4;
            numsommets[1]=1;
            break;
    }
}
//normalement aucun check à passer pour vérifier le conflit t==1 et *numaret==4
//on part du principe que si t==1, on ne transmettra pas *numaret==4 à la fonction 