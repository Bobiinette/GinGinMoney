#ifndef SOLVEUR2_H
#define SOLVEUR2_H

#include "ComposanteConnexe.h"
#include "Grille.h"
#include "ListeComposanteConnexe.h"
#include <stdbool.h>

/*! \fn void solveur(char *chemin,TabComposanteConnexe tab, Case **grille)
 *  \brief Permet de lancer le solveur
 *  \param chemin pointeur vers l'emplacement du fichier dans lequel le solveur donnera sa solution
 *  \param tab l'ensemble des composantes connexes
 *  \param grille grille de jeu
*/
void solveur(char *chemin,TabComposanteConnexe tab, Case **grille);

/*! \fn ComposanteConnexe *changementCouleur(ComposanteConnexe *ccInitiale, TabComposanteConnexe toutesComposantesConnexes, Couleur nouvelleCouleur)
 *\brief Fonction qui permet le changement de couleur d'une composante connexe. Met à jour les composantes connexes voisines de la composante connexe (ne s'occupe pas des cases).
 *\param ccInitiale La composante connexe dont on veut changer le couleur.
 *\param touteComposantesConnexes Un pointeur vers la liste de toutes les composantes connexes.
 *\param nouvelleCouleur La nouvelle couleur de ccInitiale
 *\return Renvoie la composante connexe avec la nouvelle couleur et composantes connexes voisines mis à jour.
 */
ComposanteConnexe *changementCouleurComposanteConnexe(ComposanteConnexe *ccInitiale, TabComposanteConnexe *toutesComposantesConnexes, Couleur nouvelleCouleur);

/*! \TabComposanteConnexe copieTabCompoConnexe(TabComposanteConnexe tab)
 *  \brief Crée une copie une TabComposanteConnexe
 *  \param tab la TabComposanteConnexe à copier
 *  \return une TabComposanteConnexe qui est la copie de tab
*/
TabComposanteConnexe copieTabCompoConnexe(TabComposanteConnexe tab);

/*! \fn int couleurPresenteVoisin(TabComposanteConnexe *tab, Couleur c, Case **grille)
 *  \brief Vérifie si une composante voisine possède la couleur donnée en paramètre
 *  \param *tab pointeur vers la TabComposanteConnexe qui contient toutes les composantes connexes du plateau
 *  \param c la couleur à tester
 *  \param grille la grille de jeu
 *  \return True si la couleur c est la couleur d'au moins une composante connexe voisine, False sinon
*/
int couleurPresenteVoisin(TabComposanteConnexe *tab, Couleur c, Case **grille);

/*! \fn void solveurDeuxRecursif(TabComposanteConnexe *tab, FILE *f, int nbrCoups, int *nbrCoupsMax, Case **grille, char *test)
 *  \brief teste toutes les possibilités du jeu et écrit dans un fichier la plus pertinente
 *  \param tab pointeur vers l'ensemble des composantes connexes
 *  \param f pointeur vers le fichier
 *  \param nbrCoups nombre de coups joués
 *  \param nbrCoupsMax pointeur vers le nombre de coup optimal trouvé jusqu'à présent
 *  \param grille grille de jeu
 *  \param test chaine de caractère contenant la suite de couleur testée, c'est cette chaine de caractère qui si elle est optimale sera écrite dans le fichier f.
*/
void solveurDeuxRecursif(TabComposanteConnexe *tab, FILE *f, int nbrCoups, int *nbrCoupsMax, Case **grille, char *test);

#endif
