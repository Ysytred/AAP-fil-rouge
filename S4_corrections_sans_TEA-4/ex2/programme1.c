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

  printf("Et son nom ?\n");
  scanf("%s",nomfichier);


  FILE* fichier=NULL;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;


fichier=fopen(nomfichier,"r");
  if (fichier==NULL)
    exit(EXIT_FAILURE);

  int i=0;
    
    while (i<n){
      read=getline(&line, &len, fichier);
    	insertAVL(&root,mot);				
    	createDotAVL(root,"root");
      i++;
  	}
	return 0;
}

#include <stdio.h>
#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "avl.h"

int main(int argc, char * argv[]) {
	T_avl root = NULL; 
	T_avlNode * pAux = NULL;

	T_elt srch; 

	CLRSCR();
	WHOAMI(); 

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

  outputPath = "ex2/output";

  FILE* fichier;
  char line[30];
  size_t read;

  fichier=fopen(argv[1],"r");
  if (fichier==NULL)
      exit(EXIT_FAILURE);

  int n=atoi(argv[2]);
  int i=0;

  printf("ps de segmentation, n vaut %d", n);
  getchar();

  while (i<n){
    read=fgets(line, 30, fichier);

     printf("ps de segmentation 2");
     puts(read);
  getchar();

   	insertAVL(&root,read);	
     printf("ps de segmentation 2");
     getchar();
    createDotBST(root,"root");
     i++;
 	}
	return 0;
}
