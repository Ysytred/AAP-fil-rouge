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

char * outputPath = "."; 

/*
typedef enum {
    DOUBLE_RIGHT = -2,
    RIGHT = -1,
    BALANCED,
    LEFT,
    DOUBLE_LEFT
} T_bal;

typedef struct aNode{
	T_elt val; // élément contenu dans le noeud 
	T_bal bal; // facteur de déséquilibre
	struct aNode *l; // pointeur vers sous-arbre gauche
	struct aNode *r; // pointeur vers sous-arbre droit 
} T_avlNode, *T_avl;
*/

static T_avl newNodeAVL(T_elt e); 
static T_avlNode * rotateLeftAVL (T_avlNode * A); 
static T_avlNode * rotateRightAVL (T_avlNode * B);
static T_avlNode * balanceAVL(T_avlNode * A);

static T_avl newNodeAVL(T_elt e) {//idem fichier bst.c (cf ex1)
	
	T_avl root = (T_avlNode *) malloc(sizeof (T_avlNode)); 
	CHECK_IF(root, NULL,"erreur malloc dans newNode");
	root->val = eltdup(e); 
	root->l = NULL; 
	root->r = NULL;
	root->bal = BALANCED;
	
	return root; 
}

 

/*int	insertAVL (T_avlNode ** pA, T_elt e) {
//Attention j'ai remplacé pRoot par pA pour mieux coller au programme fourni sur le slide 90 du support de la séance 4
	int deltaH = 0;
	// ordre de récurrence ? 
	// cas de base ?
	if (*pA == NULL)
		*pA = newNodeAVL(e);
	// cas général 
	else if (eltcmp(e,(*pA)->val) <= 0 ){
		deltaH = insertAVL(&(*pA)->l, e);//insertion dans le sous arbre gauche
		(*pA)->bal += deltaH;
		printf("bal %d : %d\n", (*pA)->val, (*pA)->bal);
	}
	else{
		deltaH = insertAVL(&(*pA)->r, e);//insertion dans le sous arbre droit
		(*pA)->bal += -deltaH;//mise à jour du facteur d'équilibre
		printf("bal %d : %d\n", (*pA)->val, (*pA)->bal);
	}
	if(deltaH == 0) return 0;
	else {
		*pA = balanceAVL(*pA);
		printf("équilibrage");
	}
	if((*pA)->bal != 0) return 1;
	else return 0;
	 
}*/

int	insertAVL (T_avlNode ** pA, T_elt e) {
//Attention j'ai remplacé pRoot par pA pour mieux coller au programme fourni sur le slide 90 du support de la séance 4
	int deltaH = 0;
	// ordre de récurrence ? 
	// cas de base ?
	if (*pA == NULL){
		*pA = newNodeAVL(e);
		return 1;
	}
	// cas général 
	if (eltcmp(e,(*pA)->val) > 0)
		deltaH = -insertAVL(&(*pA)->r,e);
	else
		deltaH = insertAVL(&(*pA)->l,e);

	if(deltaH == 0) return 0;
	(*pA)->bal += deltaH;
	*pA = balanceAVL(*pA);
	return (*pA)->bal == 0 ? 0 : 1;
}


static T_avlNode * rotateLeftAVL (T_avlNode * B) {
	// rotation gauche
	T_avlNode * A = NULL;
	int a, b;
	
	if (B == NULL) return B;
	A = B->r;
	b = B->bal;
	
	if(A == NULL) return B;
	a = A->bal;
	B->r = A->l;
	A->l = B;
	/*B->bal = B->bal + 1 - ((A->bal <= 0) ? A->bal : 0);
	A->bal = A->bal + 1 + ((B->bal >= 0) ? B->bal : 0);*/
	B->bal = b + 1 + MAX2(0, -a);
	A->bal = 1 + MAX2(B->bal, 0) + a;
	return A; 
}

static T_avlNode * rotateRightAVL (T_avlNode * A) {
	// rotation droite
	T_avlNode * B = NULL;
	int a,b ;

	if (A == NULL) return A;
	B = A->l;
  	a = A->bal;

	if (B == NULL) return A;
	b = B->bal;
  	A->l = B->r;
 	B->r = A;
	A->bal = a - 1 - MAX2(b, 0);
	B->bal = b - 1 - MAX2(0, -A->bal);
	return B; 

}


static T_avlNode * balanceAVL(T_avlNode * A) {
	// rééquilibrage de A
	if (A == NULL) return A;
	if (A->bal > 1){//L'arbre penche à gauche
		if (A->l == NULL) printf("pas possible!\n");
		if((A->l)->bal < 0){
		//Le fils gauche à une branche à droite -> il faut faire rotation gauche puis droite
			A->l = rotateLeftAVL(A->l);
			A = rotateRightAVL(A);
		}
		else//Le fils gauche à une branche à gauche -> rotation simple droite
			A = rotateRightAVL(A);
		}//fin du cas l'arbe penche à gauche
	 	if (A->bal <= -2){//L'arbre penche à droite
		if(A->r == NULL) printf("pas possible!");
		if((A->r)->bal > 0){
			//Le fils droit à une branche à gauche -> il faut faire rotation droite puis gauche
			A->r = rotateRightAVL(A->r);
			A = rotateLeftAVL(A);
		}
		else//Le fils droit à une branche à droite -> rotation simple gauche
			A = rotateLeftAVL(A);
		}//fin du cas l'arbre penche à droite
	return A; 

}

// IDEM pour ABR 

void printAVL(T_avl root, int indent) {
	int i; 
	// ordre de la récurrence : hauteur de l'arbre 
	// Affiche la racine de l'arbre passé en paramètre avec un niveau d'indentation proportionnel à la profondeur du sous-arbre 

	// pas de cas de base... 
	if (root!=NULL) {
		// afficher le sous-arbre droit avec indentation+1
		printAVL(root->r, indent+1);
		// afficher le noeud racine 
		for(i=0;i<indent;i++) printf("\t");
		printf("%s\n", toString(root->val));
		// afficher le sous-arbre gauche avec indentation+1
		printAVL(root->l, indent+1);
	}
}

int heightAVL(T_avl root){
	// hauteur d'un arbre 
	int l,r; 
	if (root == NULL) return -1;

	l = heightAVL(root->l);
	r = heightAVL(root->r);

	return 1+ ((l >= r) ? l : r); 
}

int nbNodesAVL(T_avl root){
	// nb de noeuds d'un arbre (y compris les feuilles) 
	if (root == NULL) 
		return 0;
	
	return 1+ nbNodesAVL(root->l) + nbNodesAVL(root->r);
}


T_avlNode * searchAVL_rec(T_avl root, T_elt e){
	// recherche récursive

	// ordre de récurrence : hauteur de l'arbre 	
	int test; 

	// base 
	if (root== NULL) return NULL; 
	else {
		test = eltcmp(e,root->val); 
		if (test == 0) return root; // trouvé ! 
		else if (test <= 0) return searchAVL_rec(root->l,e);
		else return searchAVL_rec(root->r,e);
	}
}

T_avlNode * searchAVL_it(T_avl root, T_elt e){
	// recherche itérative

	int test;
	while(root!=NULL) {	
		test = eltcmp(e,root->val);
		if (test ==0) return root;
		else if  (test <= 0) root = root->l; 
		else root = root->r; 
	}

	// pas trouvé (ou vide)
	return NULL;  
}


static void  genDotAVL(T_avl root, FILE *fp) {
	// Attention : les fonction toString utilisent un buffer alloué comme une variable statique 
	// => elles renvoient toujours la même adresse 
	// => on ne peut pas faire deux appels à toString dans le même printf()

    fprintf(fp, "\t%s",toString(root->val)); 
    fprintf(fp, " [label = \"{<c> %s | { <g> | <d>}}\"];\n",toString(root->val));
    if (root->r == NULL && root->l == NULL) {
        fprintf(fp, "\t%s", toString(root->val)); 
		fprintf(fp, " [label = \"{<c> %s | { <g> NULL | <d> NULL}}\"];\n", toString(root->val));
	}
    else if (root->r == NULL) {
        fprintf(fp, "\t%s", toString(root->val));
		fprintf(fp, " [label = \"{<c> %s | { <g> | <d> NULL}}\"];\n", toString(root->val));
	}
	else if ( root->l == NULL) {
        fprintf(fp, "\t%s",toString(root->val));
		fprintf(fp, " [label = \"{<c> %s | { <g> NULL | <d> }}\"];\n", toString(root->val));
	}
	
    if (root->l) {
        fprintf(fp, "\t%s",toString(root->val));
		fprintf(fp, ":g -> %s;\n", toString(root->l->val));
        genDotAVL(root->l, fp);
    }

    if (root->r) {
        fprintf(fp, "\t%s",toString(root->val));
		fprintf(fp,":d -> %s;\n", toString(root->r->val));
        genDotAVL(root->r, fp);
    }
}


void createDotAVL(const T_avl root, const char *basename) {
	static char oldBasename[FILENAME_MAX + 1] = "";
	static unsigned int noVersion = 0;

	char DOSSIER_DOT[FILENAME_MAX + 1]; 
	char DOSSIER_PNG[FILENAME_MAX + 1]; 

	char fnameDot [FILENAME_MAX + 1];
	char fnamePng [FILENAME_MAX + 1];
	char	cmdLine [2 * FILENAME_MAX + 20];
	FILE *fp;
	struct stat sb;
	

	// Au premier appel, création (si nécessaire) des répertoires
	// où seront rangés les fichiers .dot et .png générés par cette fonction	

	// il faut créer le répertoire outputPath s'il n'existe pas 
	if (stat(outputPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    } else {
        printf("Création du répertoire %s\n", outputPath);
		mkdir(outputPath, 0777);
    }

	// il faut créer les répertoires outputPath/png et /dot 
	sprintf(DOSSIER_DOT, "%s/dot/",outputPath);
	sprintf(DOSSIER_PNG, "%s/png/",outputPath);

	if (oldBasename[0] == '\0') {
		mkdir(DOSSIER_DOT,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		mkdir(DOSSIER_PNG,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}

	 // S'il y a changement de nom de base alors recommencer à zéro
	 // la numérotation des fichiers 

	if (strcmp(oldBasename, basename) != 0) {
		noVersion = 0;
		strcpy(oldBasename, basename); 
	}

	sprintf(fnameDot, "%s%s_v%02u.dot", DOSSIER_DOT, basename, noVersion);
	sprintf(fnamePng, "%s%s_v%02u.png", DOSSIER_PNG, basename, noVersion);

	CHECK_IF(fp = fopen(fnameDot, "w"), NULL, "erreur fopen dans saveDotBST"); 
	
	noVersion ++;
    fprintf(fp, "digraph %s {\n", basename);
 	fprintf(fp, 
		"\tnode [\n"
			"\t\tfontname  = \"Arial bold\" \n"
			"\t\tfontsize  = \"14\"\n"
			"\t\tfontcolor = \"red\"\n"
			"\t\tstyle     = \"rounded, filled\"\n"
			"\t\tshape     = \"record\"\n"
			"\t\tfillcolor = \"grey90\"\n"
			"\t\tcolor     = \"blue\"\n"
			"\t\twidth     = \"2\"\n"
			"\t]\n"
		"\n"
		"\tedge [\n"
			"\t\tcolor     = \"blue\"\n"
		"\t]\n\n"
	);

    if (root == NULL)
        fprintf(fp, "\n");
    else
        genDotAVL(root, fp);

    fprintf(fp, "}\n");	
    fclose(fp);

    sprintf(cmdLine, "dot -Tpng  %s -o %s", fnameDot, fnamePng);
    system(cmdLine);

    printf("Creation de '%s' et '%s' ... effectuee\n", fnameDot, fnamePng);
}


int tailleDesMots()
{
	
