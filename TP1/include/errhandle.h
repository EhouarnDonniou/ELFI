#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//error_handling
int fichier_maillage_format_check(float*, float*, float*, float*, int*, int*, int*);
void bords_pas_conforme(int, int, char, char);
void n1_n2_pas_conforme(int,int);
void t_pas_conforme(int);

