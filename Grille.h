#ifndef GRILLE_H
#define GRILLE_H

enum Couleur {B,V,R,J,M,G};

typedef struct t_case Case;

int getXCase(Case test);

int getYCase(Case test);

int getCouleurCase(Case test);

void setCouleur(Case * test, Couleur c);

Case ** tableauVide(int n);

void liberationGrille(Case ** tab, int taille);


static Couleur aleatoire();

Couleur ** remplissageAleatoire(int n);


static void erreurOuverture(int check);

static void erreurLongueur(int check);

static void erreurFinFichier(int check);

static void checkCouleur(char buff);

Couleur ** remplissageFichier(char * text);
