#ifndef GRILLE_H
#define GRILLE_H

typedef enum Couleur {H,B,V,R,J,M,G} Couleur;

typedef struct Case Case;

Case * constructeurCase(int x1, int y1, Couleur c);

int getXCase(Case *test);

int getYCase(Case *test);

int getCouleurCase(Case *test);

void setCouleur(Case *test, Couleur c);


Case ** tableauVide(int n);

void liberationGrille(Case ** tab, int taille);


static Couleur aleatoire();

Case ** remplissageAleatoire(int n, Case **tab);


static void erreurOuverture(int check);

static void erreurLongueur(int check);

static void erreurFinFichier(int check);

static void checkCouleur(char buff);

Couleur conversionCharCouleur(char c);

char conversionCouleurChar(Couleur c);

char conversionEntierChar(int a);

void creationFichier(int n, char * chemin);

Case ** remplissageFichier(char * chemin, int taille);

Case * getCaseGrille(Case ** grille, int i, int j);

#endif
