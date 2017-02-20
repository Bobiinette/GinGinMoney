#include <stdio.h>
#include <stdlib.h>
#include "Cases.h"

typedef struct t_listeCase {
  Case *c;
  struct t_listeCase *suivant;
} CelluleCase, *ListeCase;

ListeCase initListeCase(void){
  return NULL;
}

int testListeCaseVide(ListeCase l){
  return (l==NULL);
}

ListeCase constructeurListeCase(Case *d, ListeCase l){
  CelluleCase *e;
  e=(CelluleCase *)malloc(sizeof(CelluleCase));
  e->c=d;
  e->suivant=l;
}

Case* getValeurListeCase(ListeCase l){
  return l->c;
}

ListeCase getSuivantListeCase(ListeCase l){
  return l->suivant;
}

void destructeurCelluleListeCase(CelluleCase *c){
  free(c);
}

void destructeurListeCase(ListeCase l){
  ListeCase ret;
  while(!testListeCaseVide(l)){
    ret=l->suivant;
    destructeurCelluleListeCase(l);
    l=ret;
  }
}

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
    m=l->suivant;
  }
  l = temporaire;
  return l;
}

void supprimeElementListeCase(Case *c, ListeCase *l){
  ListeCase temp = *l;
  ListeCase nouveauSuivant = initListeCase();
  if (testListeCaseVide(*l)){
    printf("Impossible de supprimer car aucun element");
    return;
  }
  else {
    if((*l)->c == c) {
      destructeurCelluleListeCase(*l);
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
    }
  }
  *l = temp;
}
