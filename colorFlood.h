#ifndef COLORFLOOD_H
#define COLORFLOOD_H

/**\file colorFlood.c
 *\brief Execution d'une partie.
 *		Module permettant l'execution d'une partie, mise en place d'une grille de jeu, affichage et déroulement d'une partie.
 */
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

/*! \fn void jouer(SDL_Surface *ecran)
 *  \brief permet de générer la fenêtre de jeu et ses modifications au cours de la partie
 *  \param ecran un pointeur vers la fenêtre de jeu
*/
void jouer(SDL_Surface *ecran);

/**\fn int getche(void)
*\brief C'est la fonction qui permet de gèrer ce que tape l'utilisateur sur le clavier
*\return la valeur entrée par l'utilisateur au clavier
*/
int getche(void);

/**\fn char saisirCouleur()
*\brief Cette fonction vérifie que la couleur demandé existe.
*\return la valeur correspondant à une couleur existante entrée par l'utilisateur au clavier
*/
char saisirCouleur(int nbrCoup);

/**\fn void viderBuffer()
 *\brief vider le buffer clavier
 *\param auncun
 */
void viderBuffer();

/**\fn int saisirTaille()
 *\brief Demande à l'utilisateur de saisir la taille de la grille de jeu, pour une partie en console. Cette taille dois être comprise entre 3 et 25.
 *\param aucun paramettre
 *\return la taille de la grille saisi par le joueur.
 */
int saisirTaille();

/**\fn int testTaille(int taille)
 *\brief Teste si la taille de grille demandé est bien comprise entre 3 et 25.
 *\param taille Entier qui correspond à la taille demandé pour la grille.
 *\return 1 si la taille est comprise entre 3 et 25, 0 sinon.
 */
int testTaille(int taille);

/**\fn void afficheInterLigneDessus(int taille)
 *\brief Affiche les lignes délimitant les cases du tableau pour le jeu en console
 *\param taille Entier qui correspond à la taille de la grille.
 */
void afficheLigneDessus(Case **grille, int taille, int ligne);

/**\fn void afficheInterLigneDessus(int taille)
 *\brief Affiche les cases du tableau pour le jeu en console
 *\param grille Pointeur vers la grille de jeu.
 *\param taille Entier qui correspond à la taille de la grille.
 *\param ligne Entier qui correspond au numéro de la ligne à afficher.
 */
void afficheInterLigneDessus(int taille);

/**\fn void afficheGrille(Case **grille, int taille)
 *\brief Affiche la grille en console en appelant les fonction afficheLigneDessus() et afficheInterLigneDessus().
 *\param grille Pointeur vers la grille de jeu.
 *\param taille Entier qui correspond à la taille de la grille.
 */
void afficheGrille(Case **grille, int taille);
void setGrilleTest(Case **grille, ComposanteConnexe *cc);

/**\fn int saisirTaille2D(SDL_Surface *ecran, char *str1, int min, int max)
 *\brief Demande à l'utilisateur de saisir la taille de la grille de jeu, pour une partie avec une feêntre SDL. Cette taille dois être comprise entre 3 et 25.
 *\param ecran pointeur vers la fenêtre de jeu
 *\param str1 pointeur vers la phrase à dire au joueur
 *\param min taille minimale de la grille
 *\param man taille maximale de la grille
 */
int saisirTaille2D(SDL_Surface *ecran, char *str1, int min, int max);
int changeTaille(SDL_Surface *ecran, char *str1, char *str2, int entierSaisi, int taille, int min, int max);
#endif
