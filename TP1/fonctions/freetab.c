#include <stdlib.h>
#include "../include/headers.h"

/* 
--------------------------------------------------------------------------------
  Cette fonction libere la memoire allouee par alloctab.
--------------------------------------------------------------------------------
*/
void freetab(void *ptr) {
  void **ptrT=ptr;
  free(ptrT[0]);
  free(ptr);
}
