#include <assert.h>
#include <sys/stat.h>
#include <string.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

//#define DEBUG
#include "../include/check.h"
#include <math.h>
#include "elt.h" // T_elt 
#include "avl.h" // prototypes 


char * signature(const char * mot){
  // on obtient la signature un tri basique (tri sélection)
  char * L = strdup(mot);
  char min;
  int i;
  int j;
  int imin;
  int n = 0;
  int k = 0;

  while(L[k] != 0){
    n++;
    k++;
  }
 
  for (i = 0; i < n-1; i++) {
    imin = i;
    //printf("En rentrant dans la boucle imin = %d\n", imin);
    for (j = i+1; j < n; j++){
      if (L[j] < L[imin])
        imin = j;
      //printf("j = %d\n",j);
    }
    if (i != imin){
    /*  printf("Mot avant échange : %s\n", L);
      printf("Avant l'échange imin = %d\n", imin);
      printf("L[%d] = %c, L[%d] = %c\n",i,L[i],imin,L[imin]);*/
      min = L[imin];
      L[imin] = L[i];
      L[i] = min;
      //printf("Mot après échange : %s\n\n", L);
    }
  }
  //printf("%s\n", L);
  return L;
}
