#include <stdio.h>
#include <stdlib.h>
#include "../include/headers.h"

int valq(int *t){
    switch (*t) {
        case 1 : 
            q=9;
            break;
        case 2 :
        case 3 : 
            q=3;
            break;
    } 
    return q;
}