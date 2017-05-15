#ifndef SOLVEUR_TABLEAU3_H
#define SOLVEUR_TABLEAU3_H

#include "ComposanteConnexe.h"
#include "Grille.h"
#include "solveurTableau2.h"

/**\file solveurTableau3.h
 *\brief Solveur heuristique à base de tableaux d'entiers
 *	Solution proposée pour le solveur, à base de tableaux de listes d'entiers.
 *	Ici, on cherche une solution à l'aide d'un algorithme glouton.
 *	A chaque étape, on choisit la solution qui maximise le nombre de voisins de la composante connexe principale.
 */

/**\fn  int nombreVoisinsCouleur(ListeInt** tabVoisins, ListeInt* ccPrincipale, int* appartenance, int couleur, const int taille)
 *\brief Permet de savoir le nombre de voisins que l'on gagne en choisissant la couleur.
 *\param tabVoisins Le tableau des voisins. Il n'est pas modifié par la fonction.
 *\param ccPrincipale Le tableau de 1 colonne et de 6 lignes qui correspond à la composanteConnexe principale.
 *\param appartenance La tableau qui répertorie les composantes connexes qui appartiennent à la composante connexe principale.
 *\param couleur La couleur que l'on teste.
 *\param taille Le nombre de composante connexe total. Aussi la taille de appartenance.
 *\return Le nombre de voisins que l'on gagne en choisissant la couleur.
 */
int nombreVoisinsCouleur(ListeInt** tabVoisins, ListeInt* ccPrincipale, int* appartenance, int couleur, const int taille);

/**\fn  couleurAChoisir(ListeInt** tabVoisins, ListeInt* ccPrincipale, int* appartenance, const int taille)
 *\brief Permet de savoir la couleur qui nous permet de maximiser le nombre de voisins à ce tour.
 *\param tabVoisins Le tableau des voisins. Il n'est pas modifié par la fonction.
 *\param ccPrincipale Le tableau de 1 colonne et de 6 lignes qui correspond à la composanteConnexe principale.
 *\param appartenance La tableau qui répertorie les composantes connexes qui appartiennent à la composante connexe principale.
 *\param taille Le nombre de composante connexe total. Aussi la taille de appartenance.
 *\return La couleur qui maximise le nombre de voisins.
 */
int couleurAChoisir(ListeInt** tabVoisins, ListeInt* ccPrincipale, int* appartenance, const int taille);

/**\fn ListeInt *changementCouleurSolveur3(ListeInt **tabVoisins, ListeInt *ccPrincipale, int *appartenance, const int taille, int couleur)
 *\brief Effectue les opérations nécessaires qu changement de couleur. Modifie ccPrincipale en lui affectant les nouveaux voisins qu'elle obtient avec le changement de couleur.
 *\param tabVoisins Le tableau des voisins. Il n'est pas modifié par la fonction.
 *\param ccPrincipale Le tableau qui correspond à la composanteConnexe principale.
 *\param appartenance Le tableau qui répertorie les composantes connexes qui appartiennent à la composante connexe principale. On modifie le tableau en ajoutant les nouvelle composantes connexes qui sont absorbées.
 *\param taille Le nombre de composantes connexes en tout, le nombre de colonnes de appartenance.
 *\param couleur La couleur choisie pour le changement de couleur.
 *\return Le tableau de composantes connexes modifié.
 */
ListeInt *changementCouleurSolveur3(ListeInt **tabVoisins, ListeInt *ccPrincipale, int *appartenance, const int taille, int couleur);

/**\fn  char* solveurEtape3(ListeInt **tabVoisins, ListeInt *ccPrincipale, int *appartenance, const int taille, char *str)
 *\brief Permet de trouver une solution à une grille du colorflood. Solveur glouton.
 *\param tabVoisins Le tableau des voisins. Il n'est pas modifié par la fonction.
 *\param ccPrincipale Le tableau qui correspond à la composanteConnexe principale.
 *\param appartenance Le tableau qui répertorie les composantes connexes qui appartiennent à la composante connexe principale.
 *\param taille Le nombre de composantes connexes en tout, le nombre de colonnes des différents tableaux.
 *\param str Le tableau de char contenant la solution étudiée à l'étape actuelle.
 *\return Le nombre de coups nécessaires pour trouver la solution.
 */
char* solveurEtape3(ListeInt **tabVoisins, ListeInt *ccPrincipale, int *appartenance, const int taille, char *str);
int solveurTableau3(TabComposanteConnexe tabCC, ComposanteConnexe *cc);

#endif