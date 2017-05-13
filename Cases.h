#ifndef CASES_H
#define CASES_H

#include "Grille.h"
/*! *\file Cases.h
 *   \brief Gestion des listes de pointeurs de cases.
 *		Module permettant la gestion des listes de pointeurs de cases.
 */

 /*! \struct ListeCase
  *  \brief Structure de liste de cases.
  */
typedef struct t_listeCase CelluleCase;
typedef CelluleCase *ListeCase;

/*! \fn ListeCase initListeCase(void)
 *  \brief initialise une liste de cases.
 *  \param ne prend aucun paramètre.
 *  \return renvoie une liste vide.
 */
ListeCase initListeCase(void);

/*! \fn int testListeCaseVide(ListeCase l)
 *  \brief test si la liste de case est vide ou non.
 *  \param l une liste de cases.
 *  \return 1 si la liste de cases est vide, 0 si elle ne l'est pas.
 */
int testListeCaseVide(ListeCase l);

/*! \fn ListeCase constructeurListeCase(Case *d, ListeCase l)
 *  \brief une fonction qui permet de rajouter un élément en tête de la liste.
 *  \param d un pointeur de case.
 *  \param l une liste de cases.
 *  \return renvoie la case qui a été ajouté et le reste de la liste.
 */
ListeCase constructeurListeCase(Case *d, ListeCase l);

/*! \fn Case* getValeurListeCase(ListeCase l)
 *  \param l une liste de cases.
 *  \return le premier élément de la liste.
 */
Case* getValeurListeCase(ListeCase l);

/*! \fn ListeCase getSuivantListeCase(ListeCase l)
 *  \param l une liste de cases.
 *  \return la liste sans son premier élément.
 */
ListeCase getSuivantListeCase(ListeCase l);

/*! \fn void destructeurCelluleListeCase(CelluleCase *c)
 *  \brief une fonction qui libère l'espace mémoire associée à une cellule.
 *  \param c un pointeur d'une cellule de case
 *  \return ne renvoie rien.
 */
void destructeurCelluleListeCase(CelluleCase *c);

/*! \fn void destructeurListeCase(ListeCase l)
 *  \brief une fonction qui permet de libérer l'espace mémoire allouée d'une liste de cases.
 *  \param l une liste de cases.
 *  \return ne renvoie rien.
 */
void destructeurListeCase(ListeCase l);

/*! \fn int estPresentDansListeCase(Case *c, ListeCase l)
 *  \brief une fonction qui cherche dans une liste de cases si une case est présente ou non.
 *  \param c un pointeur de case.
 *  \param l une liste de cases.
 *  \return 1 si la case cherchée est dans la liste, 0 sinon.
 */
int estPresentDansListeCase(Case *c, ListeCase l);

/*! \fn ListeCase concatenationListeCase(ListeCase l, ListeCase m)
 *  \brief une fonction qui permet de concaténer deux listes de cases.
        Modifie le premier argument passé en paramètre.
 *  \param l la liste de cases de début.
 *  \param m la liste de cases de fin.
 *  \return la concatenation de deux listes.
 */
ListeCase concatenationListeCase(ListeCase l, ListeCase m);

/*! \fn void supprimeElementListeCase(Case *c, ListeCase l)
 *  \brief une fonction qui permet de supprimer un élément d'une liste et de libérer la mémoire qui y est allouée.
 *  \param c un pointeur de case.
 *  \param l la liste dans laquelle on veut supprimer un élément.
 *  \return la liste moins l'élément qui a été supprimé.
 */
ListeCase supprimeElementListeCase(Case *c, ListeCase l);

/**\fn int longueurListeCase(ListeCase l)
 *\brief permet de savoir la longueur d'une liste case.
 *        Utile pour les tests unitaires.
 *\param l La liste de case dont on veut la longueur.
 *\return La longueur de la liste passée en paramètres.
 */
int longueurListeCase(ListeCase l);

#endif
