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

/**\fn  ListeInt initListeInt(void)
 *\brief Initialise un ListeInt à NULL.
 *\param void
 *\return NULL
 */
 ListeInt initListeInt();

/**\fn  ListeInt constructeurListeInt(int v, ListeInt l)
 *\brief Alloue la mmoire pour un nouvel ellement et ajoute un élément en tête de la liste.
 *\param v L'entier à ajouter.
 *\param l La liste à laquelle on rajoute l'entier.
 *\return La liste avec l'élément v rajouté en tête.
 */
 ListeInt constructeurListeInt(int v, ListeInt l);

/**\fn  void destructeurCelluleListeInt(CelluleListeInt *c)
 *\brief Libère la mémoire allouée à un élément d'un ListeInt.
 *\param c Un pointeur vers l'élément de la liste à libérer.
 *\return void
 */
 void destructeurCelluleListeInt(CelluleListeInt *c);

/**\fn  void destructeurListeInt(ListeInt l)
 *\brief Libère la mémoire allouée à un ListeInt, en faisant appel à destructeurCelluleListeInt.
 *\param l Le ListeInt dont on veut libérer la mémoire.
 *\return void
 */
 void destructeurListeInt(ListeInt l);

/**\fn  int estPresentDansListeInt(int v, ListeInt l)
 *\brief Permet de savoir si un élément est présent dans un ListeInt ou non.
 *\param v L'entier dont on veut savoir la présence ou non.
 *\param l Le ListeInt dans lequel on fait la recherche. 
 *\return 1 si l'élément est présent dans la liste, 0 sinon.
 */
 int estPresentDansListeInt(int v, ListeInt l);

/**\fn  ListeInt concatenationListeInt(ListeInt l1, ListeInt l2)
 *\brief Permet la concaténation de 2 ListeInt. On rajoute les éléments de l2 à l1, donc l1 est modifiée.
 *\param l1 La première liste à concaténer. La liste l1 est modifiée.
 *\param l2 La deuxièmre liste à concaténer. l2 n'estas modifiée.
 *\return La liste l1 avec les éléments de l2 rajoutés.
 */
 ListeInt concatenationListeInt(ListeInt l1, ListeInt l2);

/**\fn  ListeInt concatenationListeIntTestAppartenance(ListeInt l1, ListeInt l2, int *appartenance)
 *\brief Permet la concaténation de 2 ListeInt, avec prise en compte de l'aggrandissement de la composante connexe principale. On rajoute les éléments de l2 à l1, donc l1 est modifiée.
 *	Le tableau d'appartenance est un tableau avec n colonnes, n étant le nombre de composantes connexes, qui vaut 1 si la composante connexe appartient à la composante connexe principale, 0 sinon.
 *\param l1 La première liste à concaténer. La liste l1 est modifiée.
 *\param l2 La deuxièmre liste à concaténer. l2 n'estas modifiée.
 *\param appartenance Le tableau d'appartenance, qui permet de déterminer si une composante cnnexe appartient à la composante connexe principale.
 *\return La liste l1 avec les éléments de l2 rajoutés, sans les éléments de l2 qui ont étés absorbés par la composante connexe principale.
 */
 ListeInt concatenationListeIntTestAppartenance(ListeInt l1, ListeInt l2, int *appartenance);

/**\fn  int longueurListeInt(ListeInt l)
 *\brief Permet d'obtenir la taille d'un ListeInt.
 *\param l La liste dont on veut la taille.
 *\return La taille de l, 0 si l vaut NULL.
 */
 int longueurListeInt(ListeInt l);

/**\fn  ListeInt **creeTabVoisins(TabComposanteConnexe tabCC, int taille)
 *\brief Permet de transformer un TabComposanteConnexe en un tableau de taille colonnes et 6 lignes de ListeInt, pour l'utiliser dans le solveur.
 * 	Les 6 lignes correspondant aux 6 couleurs.
 *\param tabCC La liste des composantes connexes générées à partir de la grille.
 *\param taille La taille du TabComposanteConnexe et le nombre de colonnes du ListeInt, à savoir le nombre de composantes connexes de la grille.
 *\return Le ListeInt correspondant au TabComposanteConnexe.
 */
 ListeInt **creeTabVoisins(TabComposanteConnexe tabCC, int taille);

/**\fn  void detruitTabVoisins(ListeInt **tab, int taille)
 *\brief Libère la mémoire allouée à un tableau de taille colonnes et 6 lignes.
 *\param tab Le tableau dont on veut libérer la mémoire.
 *\param taille Le nombre de colones du tableau dont on veut libérer la mémoire.
 *\return void
 */
 void detruitTabVoisins(ListeInt **tab, int taille);

/**\fn  int **miseAjour(int **appartenance, const int taille, int a)
 *\brief Copie les valeurs de la colonne a-1 de appartenance dans la colonne a.
 *\param appartenance Le tableau de ListeInt que l'ont veut mettre à jour.
 *\param taille La taille du tableau de ListeInt.
 *\param a L'étape à mettre à jour.
 *\return Le tableau avec les colones a-1 et a identiques.
 */
 int **miseAjour(int **appartenance, const int taille, int a);

/**\fn  ListeInt **miseAjourCC(ListeInt **ccInitiale, const int taille, int a)
 *\brief Copie les valeurs de la colonne a-1 de ccInitiale dans la colonne a.
 *\param ccInitiale Le tableau de ListeInt que l'ont veut mettre à jour.
 *\param taille La taille du tableau de ListeInt.
 *\param a L'étape à mettre à jour.
 *\return Le tableau avec les colones a-1 et a identiques.
 */
 ListeInt **miseAjourCC(ListeInt **ccInitiale, const int taille, int a);

/**\fn  int nombreVoisinsNonNull(ListeInt *ccPrincipale)
 *\brief Compte le nombre de voisins non nuls d'une composante connexe.
 *\param ccInitiale Le tableau à une dimmension de ListeInt dont on veut le nombre de voisins non nuls.
 *\return Le nombre de voisins non nuls de la composante connexe passée en argument.
 */
 int nombreVoisinsNonNull(ListeInt *ccPrincipale);

/**\fn  ListeInt **changementCouleurSolveur(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **deplacement, const int taille, int couleur, int nombreCoups)
 *\brief Effectue les opérations nécessaires qu changement de couleur. Modifie la colone nombreCoups de ccPrincipale en lui affectant les nouveaux voisins qu'elle obtient avec le changement de couleur.
 *\param tabVoisins Le tableau des voisins. Il n'est pas modifié par la fonction.
 *\param ccPrincipale Le tableau qui correspond à la composanteConnexe principale à plusieurs étapes. L'étape nombreCoups est modifiée par la fonction.
 *\param appartenance La tableau qui répertorie les composantes connexes qui appartiennent à la composante connexe principale. On modifie le tableau en ajoutant les nouvelle composantes connexes qui sont absorbées.
 *\param taille Le nombre de composantes connexes en tout, le nombre de colonnes des différents tableaux.
 *\param couleur La couleur choisie pour le changement de couleur.
 *\param nombreCoups L'étape actuelle. Sert pour se placer dans les taleaux.
 *\return Le tableau de composantes connexes modifié.
 */
 ListeInt **changementCouleurSolveur(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **appartenance, const int taille, int couleur, int nombreCoups);

/**\fn  void solveurEtape(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **appartenance, const int taille, int *tailleMax, FILE **f, char *str, int nbrCoups)
 *\brief Effectue une étape du solveur. Fait un changement de couleur, ou met à jour la solution si on trouve une meilleure solution.
 *\param tabVoisins Le tableau des voisins. Il n'est pas modifié par la fonction.
 *\param ccPrincipale Le tableau qui correspond à la composanteConnexe principale à plusieurs étapes. L'étape nbrCoups est modifiée par la fonction.
 *\param appartenance La tableau qui répertorie les composantes connexes qui appartiennent à la composante connexe principale.
 *\param taille Le nombre de composantes connexes en tout, le nombre de colonnes des différents tableaux.
 *\param tailleMax Un pointeur vers la meilleure solution trouvée.
 *\param str Le tableau de char contenant la solution étudiée à l'étape actuelle.
 *\param nbrCoups Le nombre de coups de la solution actuelle.
 *\return Le tableau de composantes connexes modifié.
 */
 void solveurEtape(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **appartenance, const int taille, int *tailleMax, FILE **f, char *str, int nbrCoups);

/**\fn  void solveurTableau2(TabComposanteConnexe tabCC, ComposanteConnexe *cc)
 *\brief Trouve une solution pour résoudre le colorFlood en un nombre minimum de coups.
 *\param tabCC Le tabComposanteConnexe qui contient toutes les composantes connexes de la grille à résoudre.
 *\param cc Un pointeur vers la composante connexe principale.
 *\return Le nombre de coups pour résoudre la grille.
 */
int solveurTableau2(TabComposanteConnexe tabCC, ComposanteConnexe *cc);

#endif