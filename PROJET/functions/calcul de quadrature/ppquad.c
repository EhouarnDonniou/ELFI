/*
--------------------------------------------------------------------------------
    Dora PAPAI, Ehouarn DONNIOU, Damien MALETTE

    Ecrit le /2026
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../include/headerTP2a.h"

void ppquad(int t, float* poids, float** pts){
    switch (t){
        // quadrangle (ordre 3) q=9
        case 1 : 

            //vecteur poids
            for (int i=0; i<5; i++){
                poids[i]=1/36;
            }
            for (int i=4; i<8; i++){
                poids[i]=1/9;
            }
            poids[8]=4/9;

            //matrice des points de quadrature
            pts[0][0]=1;    //x1
            pts[0][1]=0;

            pts[1][0]=1;    //x2
            pts[1][1]=1;

            pts[2][0]=0;    //x3
            pts[2][1]=1;

            pts[3][0]=0;    //x4
            pts[3][1]=0;

            pts[4][0]=1;    //x5
            pts[4][1]=1/2;

            pts[5][0]=1/2;  //x6
            pts[5][1]=1;

            pts[6][0]=0;    //x7
            pts[6][1]=1/2;

            pts[7][0]=1/2;  //x8
            pts[7][1]=0;

            pts[8][0]=1/2;  //x9
            pts[8][1]=1/2;

            break;

        // triangle (orde 2) q=3
        case 2 : 

            //vecteur poids
            for (int i=0; i<2; i++){
                poids[i]=1/6;
            }

            //matrice des points de quadrature
            pts[0][0]=1/2;  //x1
            pts[0][1]=1/2;

            pts[1][0]=0;    //x2
            pts[1][1]=1/2;

            pts[2][0]=1/2;  //x3
            pts[2][1]=0;
            break;

        
        // segment (ordre 3) q=3
        case 3 : 

            //vecteur poids
            poids[1]=1/6;
            poids[2]=1/6;
            poids[3]=2/3;

            //matrice des points de quadrature
            pts[0][0]=1;    //x1
            pts[1][0]=0;    //x2
            pts[2][0]=1/2;  //x3
            break;

            
    }//x3

}