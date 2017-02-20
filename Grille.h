#ifndef GRILLE_H
#define GRILLE_H

typedef enum Couleur {B,V,R,J,M,G} Couleur;

typedef struct Case Case;

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

Couleur ** remplissageFichier(char * text);

#endif