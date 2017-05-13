#ifndef SOLVEUR_TABLEAU3_H
#define SOLVEUR_TABLEAU3_H

#include "ComposanteConnexe.h"
#include "Grille.h"
#include "solveurTableau2.h"

/**\file solveurTableau3.h
 *\brief Solveur à base de tableaux d'entiers
 *	Solution proposée pour le solveur, à base de tableaux de listes d'entiers.
 *	On attribue ici un numéro à chaque composante connexe, et on voit une composante connexe comme un tableau avec 1 colonne et 6 lignes, chaque ligne représantant une couleur de la composante connexe.
 *	Dans chaque ligne, on a une liste de voisins correspondant aux voisins de la composante connexe, avec la couleur correspondant à la ligne sélectionnée.
 */

int nombreVoisinsCouleur(ListeInt** tabVoisins, ListeInt* ccPrincipale, int* appartenance, int couleur, const int taille);
int couleurAChoisir(ListeInt** tabVoisins, ListeInt* ccPrincipale, int* appartenance, const int taille);
char* solveurEtape3(ListeInt **tabVoisins, ListeInt *ccPrincipale, int *appartenance, const int taille, char *str);
int solveurTableau3(TabComposanteConnexe tabCC, ComposanteConnexe *cc);

#endif