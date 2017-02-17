#include "ListeComposanteConnexe.h"
#include "ComposanteConnexe.h"

struct t_ListeComposanteConnexe{
  ComposanteConnexe composantec;
  struct ListeComposanteConnexe *suivant;
}

ListeComposanteConnexe initListeComposanteConnexe(void){
  return NULL;
}

int estVideListeComposanteConnexe(ListeComposanteConnexe l){
  return (l==NULL);
}

ComposanteConnexe getValeurListeComposanteConnexe(ListeComposanteConnexe l){
  return l->composantec;
}

ListeComposanteConnexe getSuivantListeComposanteConnexe(ListeComposanteConnexe l){
  return l->suivant;
}

ListeComposanteConnexe constructeurListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe c){
  CelluleComposanteConnexe *compoconnexe;
  compoconnexe=(CelluleComposanteConnexe *)malloc(sizeof(CelluleComposanteConnexe));
  compoconnexe->composantec=c;
  compoconnexe->suivant=l;
  return compoconnexe;
}

void destructeurListeComposanteConnexe(ListeComposanteConnexe l){
  ComposanteConnexe cc;
  while (!estVideListeComposanteConnexe(l)){
    cc=getValeurListeComposanteConnexe(l);
    l=getSuivantListeComposanteConnexe(l);
    destructeurComposanteConnexe(cc);
  }
  free(l);
}

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


ComposanteConnexe *rechercheElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe element){
  while(!(estVideListeComposanteConnexe(l)){
    if(estIdentique(element,l->composantec))){
      return &(l->composantec);
    }
    l=l->suivant;
  }
  return NULL;
}

void supprimeElementListeComposanteConnexe(ListeComposanteConnexe *l, ComposanteConnexe element){
  ListeComposanteConnexe res;
  res=initListeComposanteConnexe();
  if (rechercheElementListeComposanteConnexe(*l,element)!=NULL){
    while (!estVideListeComposanteConnexe(*l)){
      if(element!==*l->composantec){
        res=constructeurListeComposanteConnexe(res,*l->composantec);
      }
      *l=*l->suivant;
    }
    while (!estVideListeComposanteConnexe(res)){
      l=constructeur(*l,res->composantec);
      res=res->suivant;
    }
  }
}
