#ifndef COLORFLOOD_SDL_H
#define COLORFLOOD_SDL_H

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
/*! *\file colorFlood_SDL.h
 *   \brief Création de la grille sous la forme 2D.
 *		Module permettant la création de la grille sous forme 2D.
 */

 /*! \fn SDL_Surface* initFenetre()
  *  \brief permet la création d'une fenêtre de jeu.
  *  \param ne prend aucun paramètre.
  *  \return renvoie une fenêtre de jeu.
  */
SDL_Surface* initFenetre();

/*! \fn void menu(SDL_Surface *ecran)
 *  \brief permet la création de l'écran de menu de jeu affichant "Bienvenue dans le Color Flood de GinGinMoney !" ainsi que l'encadré "Jouer".
 *  \param *ecran qui est le pointeur de l'écran de jeu.
 *  \return rien.
 */
void menu(SDL_Surface *ecran);

/*! \fn void maj(SDL_Surface *ecran)
 *  \brief permet de mettre en blanc la fenêtre de jeu.
 *  \param *ecran qui représente le pointeur de l'ecran c'est-à-dire de la fenêtre de jeu.
 *  \return rien.
 */
void maj(SDL_Surface *ecran);

/*! \fn void saisieTaille2D(SDL_Surface *ecran, char *str1, char *str2)
 *  \brief permet de rentrer la taille de la grille avec laquelle l'on souhaite jouer.
 *  \param *ecran qui est le pointeur de l'ecran de jeu.
 *  \param *str1 un pointeur de char où l'on rentrera la demande de la taille de la grille.
 *  \param *str2 un pointeur de char où l'on rentrera la réponse à la question précédente.
 *  \return rien.
 */
void saisieTaille2D(SDL_Surface *ecran, char *str1, char *str2);

/*! \fn void afficheGrille2D(int tailleGrille, Case **tab, SDL_Surface *ecran, char *str)
 *  \brief permet d'afficher la grille du Color Flood.
 *  \param tailleGrille qui est la taille de la grille rentrée par l'utilisateur.
 *  \param tab un pointeur de pointeur d'une case.
 *  \param *ecran le pointeur de l'écran de jeu.
 *  \param *str un pointeur de char qui affichera le nombre de coups restanats à l'utilisateur.
 *  \return rien.
 */
void afficheGrille2D(int tailleGrille, Case **tab, SDL_Surface *ecran, char *str);

/*! \fn void endroitClique(int *i, int *j, int nombre_Cases, int x_clique, int y_clique)
 *  \brief permet de savoir sur quelle case l'utilisateur a cliqué.
 *  \param *i le pointeur de la coordonnée verticale de la case cliquée.
 *  \param *j le pointeur de la coordonnée horizontale de la case cliquée.
 *  \param nombre_Cases permet de savoir le nombre de cases de la grille.
 *  \param x_clique la coordonnée verticale.
 *  \param y_clique la coordonnée horizontale.
 *  \return rien.
 */
void endroitClique(int *i, int* j, int nombre_Cases, int x_clique, int y_clique);

/*! \fn void quitter()
 *  \brief permet de libérer l'espace mémoire alloué à l'écriture et à l'affichage de l'écran.
 *  \param ne prend aucun paramètre.
 *  \return rien.
 */
void quitter();

/*! \fn int choixMenu(int x, int y)
 *  \brief permet de savoir si l'utilisateur a bien cliqué sur "Jouer" dans le menu.
 *  \param x coordonnée verticale.
 *  \param y coordonnée horizontale
 *  \return rien.
 */
int choixMenu(int x, int y);

#endif
