#ifndef SOLVEUR_TABLEAU_H
#define SOLVEUR_TABLEAU_H

#include "ComposanteConnexe.h"
#include "Grille.h"

/**\file solveurTableau2.h
 *\brief Solveur à base de tableaux d'entiers
 *	Solution proposée pour le solveur, à base de tableaux de listes d'entiers.
 *	On attribue ici un numéro à chaque composante connexe, et on voit une composante connexe comme un tableau avec 1 colonne et 6 lignes, chaque ligne représantant une couleur de la composante connexe.
 *	Dans chaque ligne, on a une liste de voisins correspondant aux voisins de la composante connexe, avec la couleur correspondant à la ligne sélectionnée.
 */

/**\struct ListeInt
 *\brief Structure de liste d'entiers.
 */
typedef struct t_CelluleListeInt CelluleListeInt;
typedef CelluleListeInt *ListeInt;

/**\fn static void solveurTableau2(TabComposanteConnexe tabCC, ComposanteConnexe *cc)
 *\brief Trouve une solution pour résoudre le colorFlood en un nombre minimum de coups.
 *\param tabCC Le tabComposanteConnexe qui contient toutes les composantes connexes de la grille à résoudre.
 *\param cc Un pointeur vers la composante connexe principale.
 *\return Le nombre de coups pour résoudre la grille.
 */
int solveurTableau2(TabComposanteConnexe tabCC, ComposanteConnexe *cc);

#endif