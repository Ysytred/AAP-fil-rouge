#include <stdio.h>
#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "avl.h"
#include "fp2.h"

int main(int argc, char ** argv) {
	T_avl root = NULL; 
	T_avlNode * pAux = NULL;

	T_elt srch; 

	CLRSCR();
	WHOAMI(); 

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
  outputPath = "ex2/output";
  char *nom0 = "FLORENT";
  char * sig0 = signature(nom0);
  char *nom1 = "CAMILLE";
  char * sig1 = signature(nom1);
  char *nom2 = "PAUL";
  char * sig2 = signature(nom2);
  char *nom3 = "LUCAS";
  char * sig3 = signature(nom3);
  printf("signature de %s : %s\n",nom0, sig0);
  printf("signature de %s : %s\n",nom1, sig1);
  printf("signature de %s : %s\n",nom2, sig2);
  printf("signature de %s : %s\n",nom3, sig3);
	//createDotAVL(root, "root");

	return 0;
}







