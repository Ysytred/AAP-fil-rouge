#include "elt.h" // T_elt 

#ifndef _AVL_H_
#define _AVL_H_

#define	MAX2(a, b)	    ((a) >= (b) ? (a) : (b))
#define	MIN2(a, b)	    ((a) <= (b) ? (a) : (b))
#define	MAX3(a, b, c)	((a) >= (b) ? MAX2(a, c) : MAX2(b, c))
#define	MIN3(a, b,c )	((a) <= (b) ? MIN2(a, c) : MIN2(b, c))

// Type définissant le facteur d'équilibre (bal) d'un noeud d'un arbre binaire
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


typedef struct nodeSign {
	T_elt sign; //signature des mots dans le noeud
	T_elt * val; //liste des mots contenus dans le noeud 
	T_bal bal; // facteur de déséquilibre
	struct nodeSign *l; // pointeur vers sous-arbre gauche
	struct nodeSign *r; // pointeur vers sous-arbre droit 
} T_avlNodeSign, *T_avlSign;
	
	
extern char * outputPath;

int	insertAVL (T_avlNode ** root, T_elt e);
void printAVL(T_avl root, int indent); 
int heightAVL(T_avl);
int nbNodesAVL(T_avl);
T_avlNode * searchAVL_rec(T_avl root, T_elt e);
T_avlNode * searchAVL_it(T_avl root, T_elt e);
void fusionner(T_elt t [], int d, int m, int f);
void signature(T_elt t [], int debut, int fin); 
int tailleDesMots();
int nbMots(T_elt adresse_fichier, T_elt nom_fichier);
int hauteurMin(T_avl root);

void createDotAVL(const T_avl root, const char *basename); 



#endif 


