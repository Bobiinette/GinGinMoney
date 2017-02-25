#include <stdlib.h>

#include "ListeComposanteConnexe.h"

/*! *\file ListeComposanteConnexe.c
 *   \brief Gestion des listes de pointeurs de composantes connexes.
 *		Module permettant la gestion des listes de pointeurs de composantes connexes.
 */

/*! \struct t_ListeComposanteConnexe ListeComposanteConnexe.h "inc/ListeComposanteConnexe.h"
 *  \brief Structure de Liste de pointeurs Composantes connexes
*/
struct t_ListeComposanteConnexe{
  ComposanteConnexe *composantec;/**< Composante connexe en tête de liste*/
  struct t_ListeComposanteConnexe *suivant;/**< Queue de la Liste de composantes connexes*/
};
/*! \fn ListeComposanteConnexe initListeComposanteConnexe(void)
 *  \brief Permet d'initialiser une ListeComposanteConnexe
 *  \param Ne prend aucun paramettre
 *  \return Liste NULL
*/

ListeComposanteConnexe initListeComposanteConnexe(void){
    return NULL;
}

/*! \fn int estVideListeComposanteConnexe(ListeComposanteConnexe l)
 *  \brief Vérifie si une ListeComposanteConnexe est vide
 *  \param l la ListeComposanteConnexe dont on veut vérifier si elle est vide ou non
 *  \return 1 si la liste est vide, 0 si elle ne l'est pas
*/
int estVideListeComposanteConnexe(ListeComposanteConnexe l){
    return (l==NULL);
}

/*! \fn ComposanteConnexe getValeurListeComposanteConnexe(ListeComposanteConnexe l)
    \brief Getter pour obtenir la première ComposanteConnexe de la ListeComposanteConnexe
 *  \param l la ListeComposanteConnexe dont on veut le premier élèment
 *  \return Premier élèment de ListeComposanteConnexe
*/
ComposanteConnexe* getValeurListeComposanteConnexe(ListeComposanteConnexe l){
    return l->composantec;
}

/*! \fn ComposanteConnexe getValeurListeComposanteConnexe(ListeComposanteConnexe l)
    \brief Getter pour obtenir la queue de la ListeComposanteConnexe
 *  \param l la ListeComposanteConnexe dont on veut la queue
 *  \return Queue de la ListeComposanteConnexe
*/
ListeComposanteConnexe getSuivantListeComposanteConnexe(ListeComposanteConnexe l){
    return l->suivant;
}

/*! \fn ListeComposanteConnexe constructeurListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *c)
 *  \brief Rajoute un élément en tête de la ListeComposanteConnexe.
 *  \param l la ListeComposanteConnexe que l'on veut modifier
 *  \param c pointeur vers la ComposanteConnexe que l'on veut ajouter à la liste
 *  \return ListeComposanteConnexe l dans laquelle l'élèment c a été ajouté
*/
ListeComposanteConnexe constructeurListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *c){
    CelluleComposanteConnexe *compoconnexe;
    compoconnexe=(CelluleComposanteConnexe *)malloc(sizeof(CelluleComposanteConnexe));
    compoconnexe->composantec = c;
    compoconnexe->suivant = l;
    return compoconnexe;
}

/*! \fn void destructeurCelluleListeComposanteConnexe(CelluleComposanteConnexe *c)
 *  \brief Libère l'espace mémoire alloué pour une cellule de ListeComposanteConnexe
 *  \param *c pointeur de CelluleComposanteConnexe que l'on veut détruire pour libérer la mémoire
*/
void destructeurCelluleListeComposanteConnexe(CelluleComposanteConnexe *c) {
    free(c);
}

/*! \fn void destructeurListeComposanteConnexe(ListeComposanteConnexe l)
 *  \brief Libère l'espace mémoire alloué pour une ListeComposanteConnexe
 *  \param l la ListeComposanteConnexe que l'on veut détruire pour libérer la mémoire
*/
void destructeurListeComposanteConnexe(ListeComposanteConnexe l){
    ListeComposanteConnexe tmp;
    while (!estVideListeComposanteConnexe(l)){
        tmp = l;
        l = l->suivant;
        destructeurCelluleListeComposanteConnexe(tmp);
    }
}

/*! \fn int longeurListeComposanteConnexe(ListeComposanteConnexe l)
 *  \brief Calcul la longueur de la ListeComposanteConnexe
 *  \param l la ListeComposanteConnexe dont on veut la longuer
 *  \return La longueur de la ListeComposanteConnexe l
*/
int longeurListeComposanteConnexe(ListeComposanteConnexe l){
	int longeur=0;
    while (!estVideListeComposanteConnexe(l)){
        longeur=longeur+1;
        l=l->suivant;
    }
    return longeur;
}

/*! \fn ComposanteConnexe *rechercheElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *element)
 *  \brief Recherche si un élément est dans la ListeComposanteConnexe
 *  \param l la ListeComposanteConnexe dans laquelle on recherche l'élément
 *  \param element pointeur vers la ComposanteConnexe que l'on cherche dans la liste
 *  \return Le pointeur vers l'élèment recherché si trouvé, Renvoie NULL sinon
*/
ComposanteConnexe *rechercheElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *element){
  ListeComposanteConnexe save = l;
  ComposanteConnexe *cc = NULL;
  while(!(estVideListeComposanteConnexe(save))){
      if(estIdentique(save->composantec, element)){
          cc = save->composantec;
          return cc;
      }
      save=save->suivant;
    }
    return NULL;
}

/*! \fn void supprimeElementListeComposanteConnexe(ListeComposanteConnexe *l, ComposanteConnexe *element)
 *  \brief Supprime un élément de ListeComposanteConnexe
 *  \param l pointeur vers la ListeComposanteConnexe dans laquelle on veut supprimer un élément
 *  \param element pointeur vers la  ComposanteConnexe que l'on veut supprimer
*/
void supprimeElementListeComposanteConnexe(ListeComposanteConnexe *l, ComposanteConnexe *element){
    ListeComposanteConnexe tmp = initListeComposanteConnexe();
    ListeComposanteConnexe save = initListeComposanteConnexe();
    save = *l;
    if (rechercheElementListeComposanteConnexe(*l,element)!=NULL){

        if((*l)->composantec == element) {
            *l = (*l)->suivant;
            destructeurCelluleListeComposanteConnexe(save);
        }
        else {
            while (!estVideListeComposanteConnexe((*l)->suivant)){
                if(element == ((*l)->suivant)->composantec){
                    tmp = (*l)->suivant;
                    (*l)->suivant = ((*l)->suivant)->suivant;
                }
                *l = (*l)->suivant;
            }
            *l = save;
        }
    }
}
