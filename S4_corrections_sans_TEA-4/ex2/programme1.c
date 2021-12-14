#include <stdio.h>
#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "avl.h"

T_elt mot;
T_elt nom_fichier;

int main() {

	CLRSCR();

  outputPath = "ex2/output";


	T_avl root = NULL; 
	T_avlNode * pAux = NULL;
	
	int n=0;
  char mot[30];
  char nomfichier[40];
	
	printf("choisir un nombre de mots à mettre dans l'arbre \n");
	scanf("%d", &n);

  printf("Et son petit nom ?\n");
  scanf("%s",nomfichier);


  FILE* fichier=NULL;
  fichier=fopen(nomfichier,"r");	
      if (fichier != NULL)
    {
        printf("Bonjour");
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }

  int i=0;
	while(i<n){
    		fgets(mot,30,nomfichier);
        /*
    		insertAVL(&pAux,mot);				
    		createDotAVL(root,"root");
*/
        i++;
  	}
  
	return 0;
}
