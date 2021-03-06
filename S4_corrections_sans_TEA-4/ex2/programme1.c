#include <stdio.h>
#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "avl.h"

#define MAX_WORD_SIZE 100

int main(int argc, char ** argv) {
	T_avl root = NULL; 
	T_avlNode * pAux = NULL;
	int n = atoi(argv[2]);//deuxième argument à rentrer en ligne de commande, correspond au nombre de noms à insérer dans l'AVL
	int i = 0;
	int k;
	char * fichier = argv[1];// argument à rentrer en ligne de commande pour indiquer quels fichier utiliser pour les prénoms
	FILE *fp = NULL;
	char str[MAX_WORD_SIZE];
	printf("%d", n);
	
	T_elt tab[n];//tab est un tableau de chaînes de caractères lorsque T_elt est définit comme chaîne de caractère
	CLRSCR();
	WHOAMI(); 
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	
 outputPath = "programme1/output";

	fp = fopen(fichier,"r");
	if(fp == NULL){
		printf("erreur fopen\n");
		return 1;
	}
	while(i < n){
	
		insertAVL(&root, fgets(str, MAX_WORD_SIZE, fp));
		printf("#-------------------------------------------------------------#\n");
		printf("i = %d\n", i);
		i++;
		printAVL(root, 0);
	}
	

	fclose(fp);	
	
	//createDotAVL(root, "root");

	return 0;
}






