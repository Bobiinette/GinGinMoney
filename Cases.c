#include <stdio.h>
#include <stdlib.h>
#include "Cases.h"
#include "Grille.h"

typedef struct t_listeCase {
  Case *c;
  struct liste *suivant;
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

void liberationCase(CelluleCase *c){
  free(c);
}

void liberationListeCase(ListeCase l){
  ListeCase ret;
  while(!testListeCaseVide(l)){
    ret=l->suivant;
    liberationCase(l);
    l=ret;
  }
}

int estPresentDansListeCase(Case *c, ListeCase l){
  int res=0;
  while(!testListeCaseVide(l)){
    if(getValeurListeCase(l)=c){
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
  ListeCase temp = l;
  ListeCase res = l;
  if (testListeCaseVide(l)){
    printf("impossible de supprimer car aucun element");
    return NULL;
  }
  else {
    while(!testListeCaseVide(l)){
      if(getValeurListeCase(res)==c){
        liberationCase(res);
        l=l->suivant;
      }
      else{
        l=l->suivant;
        res=res->suivant;
      }
    }
    printf("l'element recherche n'est pas dans la liste");
  }
}
