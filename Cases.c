#include <stdio.h>
#include <stdlib.h>
#include "Cases.h"

/*! *\file Cases.c
 *   \brief Gestion des listes de pointeurs de cases.
 *		Module permettant la gestion des listes de pointeurs de cases.
 */

/*! \struct ListeCase Cases.h
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
  CelluleCase *e = NULL;
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
  if (!testListeCaseVide(l))
    return l->c;
  return NULL;
}

/*! \fn ListeCase getSuivantListeCase(ListeCase l)
 *  \param l une liste de cases.
 *  \return la liste sans son premier élément.
 */
ListeCase getSuivantListeCase(ListeCase l){
  if(!testListeCaseVide(l)) {
      return l->suivant;
  }
  return NULL;
}

/*! \fn void destructeurCelluleListeCase(CelluleCase *c)
 *  \brief une fonction qui libère l'espace mémoire associée à une cellule.
 *  \param c un pointeur d'une cellule de case
 *  \return ne renvoie rien.
 */
void destructeurCelluleListeCase(CelluleCase *c){
  free(c);
  c = NULL;
}

/*! \fn void destructeurListeCase(ListeCase l)
 *  \brief une fonction qui permet de libérer l'espace mémoire allouée d'une liste de cases.
 *  \param l une liste de cases.
 *  \return ne renvoie rien.
 */
void destructeurListeCase(ListeCase l){
  ListeCase ret = initListeCase();
  while(!testListeCaseVide(l)){
    ret=l->suivant;
    destructeurCelluleListeCase(l);
    l = NULL;
    l = ret;
  }
  l = NULL;
}

/*! \fn int estPresentDansListeCase(Case *c, ListeCase l)
 *  \brief une fonction qui cherche dans une liste de cases si une case est présente ou non.
 *  \param c un pointeur de case.
 *  \param l une liste de cases.
 *  \return 1 si la case cherchée est dans la liste, 0 sinon.
 */
int estPresentDansListeCase(Case *c1, ListeCase l){
  int res=0;
  ListeCase tmp = l;
  while(!testListeCaseVide(tmp)){
    if(getXCase(tmp->c) == getXCase(c1) && getYCase(tmp->c) == getYCase(c1)){
      res=1;
      return res;
    }
    else{
      tmp=tmp->suivant;
    }
  }
  return res;
}

/*! \fn ListeCase concatenationListeCase(ListeCase l, ListeCase m)
 *  \brief une fonction qui permet de concaténer deux listes de cases.
        Modifie le premier argument passé en paramètre.
 *  \param l la liste de cases de début.
 *  \param m la liste de cases de fin.
 *  \return la concatenation de deux listes.
 */
ListeCase concatenationListeCase(ListeCase l, ListeCase m){
  ListeCase temporaire = NULL;
  temporaire = l;
  if(testListeCaseVide(l)){
    l = m;
    return l;
  }
  else if(testListeCaseVide(m)) {
    return l;
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

/*! \fn void supprimeElementListeCase(Case *c, ListeCase l)
 *  \brief une fonction qui permet de supprimer un élément d'une liste et de libérer la mémoire qui y est allouée.
 *  \param c un pointeur de case.
 *  \param l la liste dans laquelle on veut supprimer un élément.
 *  \return la liste moins l'élément qui a été supprimé.
 */
ListeCase supprimeElementListeCase(Case *c, ListeCase l){
  ListeCase temp = initListeCase();
  temp = l;
  ListeCase nouveauSuivant = initListeCase();
  if (testListeCaseVide(l)){
    printf("Impossible de supprimer car aucun élément\n");
  }
  else if (c==NULL){
    printf("L'élément à supprimer est NULL\n");
  }
  else {
    if(l->c == c) {
      l = l->suivant;
      destructeurCelluleListeCase(temp);
      temp = NULL;
    }
    else {
        while(!testListeCaseVide(l->suivant)){
        if((l->suivant)->c == c){
          nouveauSuivant = l->suivant;
          l->suivant = (l->suivant)->suivant;
          destructeurCelluleListeCase(nouveauSuivant);
          nouveauSuivant = NULL;
        }
        else{
          l = l->suivant;
        }
      }
      l = temp;
    }
  }
  return l;
}

/**\fn int longueurListeCase(ListeCase l)
 *\brief permet de savoir la longueur d'une liste case.
 *        Utile pour les tests unitaires.
 *\param l La liste de case dont on veut la longueur.
 *\return La longueur de la liste passée en paramètres.
 */

int longueurListeCase(ListeCase l) {
  int taille = 0;
  if(l == NULL) {
    return 0;
  }
  else {
    while(!testListeCaseVide(l)) {
      taille += 1;
      l = l->suivant;
    }
  }
  return taille;
}
