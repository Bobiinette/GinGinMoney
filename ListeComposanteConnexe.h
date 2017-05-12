#ifndef LISTE_COMPOSANTE_CONNEXE_H
#define LISTE_COMPOSANTE_CONNEXE_H
/*! *\file ListeComposanteConnexe.c
 *   \brief Gestion des listes de pointeurs de composantes connexes.
 *		Module permettant la gestion des listes de pointeurs de composantes connexes.
 */

 /*! \struct t_ListeComposanteConnexe ListeComposanteConnexe.h "inc/ListeComposanteConnexe.h"
  *  \brief Structure de Liste de pointeurs Composantes connexes
 */
typedef struct t_ListeComposanteConnexe CelluleComposanteConnexe;
typedef CelluleComposanteConnexe *ListeComposanteConnexe;

#include "ComposanteConnexe.h"

/*! \fn ListeComposanteConnexe initListeComposanteConnexe(void)
 *  \brief Permet d'initialiser une ListeComposanteConnexe
 *  \param Ne prend aucun paramettre
 *  \return Liste NULL
*/
ListeComposanteConnexe initListeComposanteConnexe(void);

/*! \fn int estVideListeComposanteConnexe(ListeComposanteConnexe l)
 *  \brief Vérifie si une ListeComposanteConnexe est vide
 *  \param l la ListeComposanteConnexe dont on veut vérifier si elle est vide ou non
 *  \return 1 si la liste est vide, 0 si elle ne l'est pas
*/
int estVideListeComposanteConnexe(ListeComposanteConnexe l);

/*! \fn ListeComposanteConnexe constructeurListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *c)
 *  \brief Rajoute un élément en tête de la ListeComposanteConnexe.
 *  \param l la ListeComposanteConnexe que l'on veut modifier
 *  \param c pointeur vers la ComposanteConnexe que l'on veut ajouter à la liste
 *  \return ListeComposanteConnexe l dans laquelle l'élèment c a été ajouté
*/
ListeComposanteConnexe constructeurListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *c);

/*! \fn int longueurListeComposanteConnexe(ListeComposanteConnexe l)
 *  \brief Calcul la longueur de la ListeComposanteConnexe
 *  \param l la ListeComposanteConnexe dont on veut la longuer
 *  \return La longueur de la ListeComposanteConnexe l
*/
int longueurListeComposanteConnexe(ListeComposanteConnexe l);

/*! \fn ComposanteConnexe getValeurListeComposanteConnexe(ListeComposanteConnexe l)
    \brief Getter pour obtenir la première ComposanteConnexe de la ListeComposanteConnexe
 *  \param l la ListeComposanteConnexe dont on veut le premier élèment
 *  \return Premier élèment de ListeComposanteConnexe
*/
ComposanteConnexe* getValeurListeComposanteConnexe(ListeComposanteConnexe l);

/*! \fn ComposanteConnexe getSuivantListeComposanteConnexe(ListeComposanteConnexe l)
    \brief Getter pour obtenir la queue de la ListeComposanteConnexe
 *  \param l la ListeComposanteConnexe dont on veut la queue
 *  \return Queue de la ListeComposanteConnexe
*/
ListeComposanteConnexe  getSuivantListeComposanteConnexe(ListeComposanteConnexe l);

/*! \fn void destructeurCelluleListeComposanteConnexe(CelluleComposanteConnexe *c)
 *  \brief Libère l'espace mémoire alloué pour une cellule de ListeComposanteConnexe
 *  \param *c pointeur de CelluleComposanteConnexe que l'on veut détruire pour libérer la mémoire
*/
void destructeurCelluleListeComposanteConnexe(CelluleComposanteConnexe *c);

/*! \fn void destructeurListeComposanteConnexe(ListeComposanteConnexe l)
 *  \brief Libère l'espace mémoire alloué pour une ListeComposanteConnexe
 *  \param l la ListeComposanteConnexe que l'on veut détruire pour libérer la mémoire
*/
void destructeurListeComposanteConnexe(ListeComposanteConnexe l);

/*! \fn ComposanteConnexe rechercheElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *element)
 *  \brief Recherche si un élément est dans la ListeComposanteConnexe
 *  \param l la ListeComposanteConnexe dans laquelle on recherche l'élément
 *  \param element pointeur vers la ComposanteConnexe que l'on cherche dans la liste
 *  \return 1 si L'élément est trouvé, Renvoie 0 sinon
*/
int rechercheElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *element);

/*! \fn void supprimeElementListeComposanteConnexe(ListeComposanteConnexe *l, ComposanteConnexe *element)
 *  \brief Supprime un élément de ListeComposanteConnexe
 *  \param l la ListeComposanteConnexe dans laquelle on veut supprimer un élément
 *  \param element pointeur vers la  ComposanteConnexe que l'on veut supprimer
 *  \return La liste de composante connexe avec l'élément supprimé
*/
ListeComposanteConnexe supprimeElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *element);

#endif
