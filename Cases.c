#include <stdio.h>
#include <stdlib.h>
#include "Cases.h"

struct t_listeCase {
  Case *c;
  struct t_listeCase *suivant;
};

ListeCase initListeCase(void){
  return NULL;
}

int testListeCaseVide(ListeCase l){
  return (l==NULL);
}

ListeCase constructeurListeCase(Case *d, ListeCase l){
  CelluleCase *e = NULL;
  e=(CelluleCase *)malloc(sizeof(CelluleCase));
  e->c=d;
  e->suivant=l;
  return e;
}

Case* getValeurListeCase(ListeCase l){
  if (!testListeCaseVide(l))
    return l->c;
  return NULL;
}

ListeCase getSuivantListeCase(ListeCase l){
  if(!testListeCaseVide(l)) {
      return l->suivant;
  }
  return NULL;
}

void destructeurCelluleListeCase(CelluleCase *c){
  free(c);
  c = NULL;
}

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

ListeCase supprimeElementListeCase(Case *c, ListeCase l){
  ListeCase temp = initListeCase();
  temp = l;
  ListeCase nouveauSuivant = initListeCase();
  if (testListeCaseVide(l)){
    printf("Impossible de supprimer car aucun élément\n");
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
