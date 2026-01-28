#include <stdlib.h>
#include "../include/headers.h"

int** alloctab(int dim1, int dim2) {
  int **ptr;

  ptr = malloc(dim1*sizeof(int *));
  if (ptr != NULL) {
    int i, taille_ligne = dim2*sizeof(int);
    int *tmp = malloc(dim1*taille_ligne);
    if (tmp != NULL) {
      for (i=0; i<dim1; i++) {
     	  ptr[i] = tmp;
  	     tmp += dim2;
      }
    }
    else {
      free(ptr);
      ptr = NULL;
    }
  }
  return(ptr);
}