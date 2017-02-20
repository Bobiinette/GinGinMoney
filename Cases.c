#include <stdio.h>
#include <stdlib.h>
#include "Cases.h"

/*! \class t_listeCase Cases.h "inc/Cases.h"
 *  \brief Structure de liste de cases.
 */
struct t_listeCase {
  Case *c;
  struct t_listeCase *suivant;
};

/*! \fn ListeCase initListeCase(void)
 *  \brief initialise une liste de cases.
 *  \param ne prend aucun paramètre.
 *  \return renvoie une liste vide.
 */
ListeCase initListeCase(void){
  return NULL;
}

/*! \fn int testListeCaseVide(ListeCase l)
 *  \brief test si la liste de case est vide ou non.
 *  \param l une liste de cases.
 *  \return 1 si la liste de cases est vide, 0 si elle ne l'est pas.
 */
int testListeCaseVide(ListeCase l){
  return (l==NULL);
}

/*! \fn ListeCase constructeurListeCase(Case *d, ListeCase l)
 *  \brief une fonction qui permet de rajouter un élément en tête de la liste.
 *  \param d un pointeur de case.
 *  \param l une liste de cases.
 *  \return renvoie la case qui a été ajouté et le reste de la liste.
 */
ListeCase constructeurListeCase(Case *d, ListeCase l){
  CelluleCase *e;
  e=(CelluleCase *)malloc(sizeof(CelluleCase));
  e->c=d;
  e->suivant=l;
  return e;
}

/*! \fn Case* getValeurListeCase(ListeCase l)
 *  \param l une liste de cases.
 *  \return le premier élément de la liste.
 */
Case* getValeurListeCase(ListeCase l){
  return l->c;
}

/*! \fn ListeCase getSuivantListeCase(ListeCase l)
 *  \param l une liste de cases.
 *  \return la liste sans son premier élément.
 */
ListeCase getSuivantListeCase(ListeCase l){
  return l->suivant;
}

/*! \fn void destructeurCelluleListeCase(CelluleCase *c)
 *  \brief une fonction qui libère l'espace mémoire associée à une cellule.
 *  \param c un pointeur d'une cellule de case
 *  \return ne renvoie rien.
 */
void destructeurCelluleListeCase(CelluleCase *c){
  free(c);
}

/*! \fn void destructeurListeCase(ListeCase l)
 *  \brief une fonction qui permet de libérer l'espace mémoire allouée d'une liste de cases.
 *  \param l une liste de cases.
 *  \return ne renvoie rien.
 */
void destructeurListeCase(ListeCase l){
  ListeCase ret;
  while(!testListeCaseVide(l)){
    ret=l->suivant;
    destructeurCelluleListeCase(l);
    l=ret;
  }
}

/*! \fn int estPresentDansListeCase(Case *c, ListeCase l)
 *  \brief une fonction qui cherche dans une liste de cases si une case est présente ou non.
 *  \param c un pointeur de case.
 *  \param l une liste de cases.
 *  \return 1 si la case cherchée est dans la liste, 0 sinon.
 */
int estPresentDansListeCase(Case *c, ListeCase l){
  int res=0;
  while(!testListeCaseVide(l)){
    if(l->c == c){
      res=1;
    }
    else{
      l=l->suivant;
    }
  }
  return res;
}

/*! \fn ListeCase concatenationListeCase(ListeCase l, ListeCase m)
 *  \brief une fonction qui permet de concaténer deux listes de cases.
 *  \param l une liste de cases.
 *  \param m une liste de cases.
 *  \return la concatenation de deux listes.
 */
ListeCase concatenationListeCase(ListeCase l, ListeCase m){
  ListeCase temporaire = l;
  if(testListeCaseVide(l)){
    printf("concatenation impossible");
    return NULL;
  }
  else{
    while(l->suivant!=NULL){
      l=l->suivant;
    }
    l->suivant = m;
  }
  l = temporaire;
  return l;
}

/*! \fn void supprimeElementListeCase(Case *c, ListeCase *l)
 *  \brief une fonction qui permet de supprimer un élément d'une liste et de libérer la mémoire qui y est allouée.
 *  \param c un pointeur de case.
 *  \param l un pointeur de liste.
 *  \return la liste moins l'élément qui a été supprimé.
 */
void supprimeElementListeCase(Case *c, ListeCase *l){
  ListeCase temp = *l;
  ListeCase nouveauSuivant = initListeCase();
  if (testListeCaseVide(*l)){
    printf("Impossible de supprimer car aucun element");
    return;
  }
  else {
    if((*l)->c == c) {
      *l = (*l)->suivant;
      destructeurCelluleListeCase(temp);
    }
    else {
        while(!testListeCaseVide((*l)->suivant)){
        if(((*l)->suivant)->c == c){
          nouveauSuivant = ((*l)->suivant)->suivant;
          destructeurCelluleListeCase((*l)->suivant);
          (*l)->suivant = nouveauSuivant;
        }
        else{
          *l = (*l)->suivant;
        }
      }
      *l = temp;
    }
  }
}
