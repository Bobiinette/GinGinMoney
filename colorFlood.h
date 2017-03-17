#ifndef COLORFLOOD_H
#define COLORFLOOD_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

void jouer(SDL_Surface *ecran);
int getche(void);
char saisirCouleur(int nbrCoup);
void viderBuffer();
int saisirTaille();
int testTaille(int taille);
void afficheLigneDessus(Case **grille, int taille, int ligne);
void afficheInterLigneDessus(int taille);
void afficheGrille(Case **grille, int taille);
void setGrilleTest(Case **grille, ComposanteConnexe *cc);
int saisirTaille2D(SDL_Surface *ecran, char *str1, int min, int max);
int changeTaille(SDL_Surface *ecran, char *str1, char *str2, int entierSaisi, int taille, int min, int max);
#endif
