#include <stdlib.h>

#include "ListeComposanteConnexe.h"

/*! \class t_ListeComposanteConnexe ListeComposanteConnexe.h "inc/ListeComposanteConnexe.h"
 *  \brief Structure de Liste de Composantes connexes
*/
struct t_ListeComposanteConnexe{
  ComposanteConnexe composantec;
  struct ListeComposanteConnexe *suivant;
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
 *  \param l une ListeComposanteConnexe
 *  \return 1 si la liste est vide, 0 si elle ne l'est pas
*/
int estVideListeComposanteConnexe(ListeComposanteConnexe l){
  return (l==NULL);
}


/*! \fn ComposanteConnexe getValeurListeComposanteConnexe(ListeComposanteConnexe l)
 *  \param l une ListeComposanteConnexe
 *  \return Premier élèment de ListeComposanteConnexe
*/
ComposanteConnexe getValeurListeComposanteConnexe(ListeComposanteConnexe l){
  return l->composantec;
}

/*! \fn ComposanteConnexe getValeurListeComposanteConnexe(ListeComposanteConnexe l)
 *  \param l une ListeComposanteConnexe
 *  \return Queue de la ListeComposanteConnexe
*/
ListeComposanteConnexe getSuivantListeComposanteConnexe(ListeComposanteConnexe l){
  return l->suivant;
}

/*! \fn ListeComposanteConnexe constructeurListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe c)
 *  \brief Rajoute un élément en tête de la ListeComposanteConnexe
 *  \param l une ListeComposanteConnexe
 *  \param c une ComposanteConnexe
 *  \return ListeComposanteConnexe l dans laquelle l'élèment c a été ajouté
*/
ListeComposanteConnexe constructeurListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe c){
  CelluleComposanteConnexe *compoconnexe;
  compoconnexe=(CelluleComposanteConnexe *)malloc(sizeof(CelluleComposanteConnexe));
  compoconnexe->composantec=c;
  compoconnexe->suivant=l;
  return compoconnexe;
}

/*! \fn void destructeurCelluleListeComposanteConnexe(CelluleComposanteConnexe *c)
 *  \brief Libère l'espace mémoire alloué pour une cellule de ListeComposanteConnexe
 *  \param *c pointeur de CelluleComposanteConnexe
*/
void destructeurCelluleListeComposanteConnexe(CelluleComposanteConnexe *c) {
  destructeurComposanteConnexe(*c);
  free(c);
}

/*! \fn void destructeurListeComposanteConnexe(ListeComposanteConnexe l)
 *  \brief Libère l'espace mémoire alloué pour une ListeComposanteConnexe
 *  \param l une ListeComposanteConnexe
*/
void destructeurListeComposanteConnexe(ListeComposanteConnexe l){
  ComposanteConnexe cc;
  while (!estVideListeComposanteConnexe(l)){
    cc=l->composantec;
    l=l->suivant;
    destructeurCelluleListeComposanteConnexe(&cc);
  }
  free(l);
}

/*! \fn int longeurListeComposanteConnexe(ListeComposanteConnexe l)
 *  \brief Calcul la longueur de la ListeComposanteConnexe
 *  \param l une ListeComposanteConnexe
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

int testVictoire(ListeComposanteConnexe l){
  int test=0;
  if(longeurListeComposanteConnexe(l)==1){
    test=1;
  }
  return test;
}

/*! \fn ComposanteConnexe *rechercheElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe element)
 *  \brief Recherche si un élément est dans la ListeComposanteConnexe
 *  \param l une ListeComposanteConnexe
 *  \param element ComposanteConnexe
 *  \return Le pointeur vers l'élèment recherché si trouvé, Renvoie NULL sinon
*/
ComposanteConnexe *rechercheElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe element){
  while(!(estVideListeComposanteConnexe(l))){
    if(estIdentique(element,l->composantec)){
      return &(l->composantec);
    }
    l=l->suivant;
  }
  return NULL;
}

/*! \fn void supprimeElementListeComposanteConnexe(ListeComposanteConnexe *l, ComposanteConnexe element)
 *  \brief Supprime un élément de ListeComposanteConnexe
 *  \param l une ListeComposanteConnexe
 *  \param element ComposanteConnexe
*/
void supprimeElementListeComposanteConnexe(ListeComposanteConnexe *l, ComposanteConnexe element){
  ListeComposanteConnexe res,res2;
  if (rechercheElementListeComposanteConnexe(*l,element)!=NULL){
    res=initListeComposanteConnexe();
    while (!estVideListeComposanteConnexe(*l)){
      if(element!==*l->composantec){
        res=constructeurListeComposanteConnexe(res,*l->composantec);
        *l=*l->suivant;
      }
      else {
        res2=*l->suivant;
        destructeurCelluleListeComposanteConnexe(&(*l->composantec));
        *l=constructeurListeComposanteConnexe(res2->suivant,res2->composantec);
      }
    }
    while (!estVideListeComposanteConnexe(res)){
      l=constructeur(*l,res->composantec);
      res=res->suivant;
    }
  }
}
