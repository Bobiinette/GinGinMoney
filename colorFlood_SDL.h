#ifndef COLORFLOOD_SDL_H
#define COLORFLOOD_SDL_H

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>

SDL_Surface* initFenetre();
void menu(SDL_Surface *ecran);
void maj(SDL_Surface *ecran);
void saisieTaille2D(SDL_Surface *ecran, char *str1, char *str2);
void afficheGrille2D(int tailleGrille, Case **tab, SDL_Surface *ecran, char *str);
void endroitClique(int *i, int* j, int nombre_Cases, int x_clique, int y_clique);
void quitter();
int choixMenu(int x, int y);

#endif