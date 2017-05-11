#include <stdlib.h>

#include "ListeComposanteConnexe.h"




struct t_ListeComposanteConnexe{
  ComposanteConnexe *composantec;/**< Composante connexe en tête de liste*/
  struct t_ListeComposanteConnexe *suivant;/**< Queue de la Liste de composantes connexes*/
};

ListeComposanteConnexe initListeComposanteConnexe(void){
    return NULL;
}

int estVideListeComposanteConnexe(ListeComposanteConnexe l){
    return (l==NULL);
}

ComposanteConnexe* getValeurListeComposanteConnexe(ListeComposanteConnexe l){
    if(!estVideListeComposanteConnexe(l)) {
        return l->composantec;
    }
    return NULL;
}

ListeComposanteConnexe getSuivantListeComposanteConnexe(ListeComposanteConnexe l){
    if(!estVideListeComposanteConnexe(l)) {
        return l->suivant;
    }
    else {
        return NULL;
    }
}

ListeComposanteConnexe constructeurListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *c){
    CelluleComposanteConnexe *compoconnexe;
    compoconnexe=(CelluleComposanteConnexe *)malloc(sizeof(CelluleComposanteConnexe));
    compoconnexe->composantec = c;
    compoconnexe->suivant = l;
    return compoconnexe;
}


void destructeurCelluleListeComposanteConnexe(CelluleComposanteConnexe *c) {
    free(c);
    c = NULL;
}


void destructeurListeComposanteConnexe(ListeComposanteConnexe l){
    ListeComposanteConnexe tmp;
    while (!estVideListeComposanteConnexe(l)){
        tmp = l;
        l = l->suivant;
        destructeurCelluleListeComposanteConnexe(tmp);
        tmp = NULL;
    }
}

int longueurListeComposanteConnexe(ListeComposanteConnexe l){
	int longeur=0;
    while (!estVideListeComposanteConnexe(l)){
        longeur=longeur+1;
        l=l->suivant;
    }
    return longeur;
}


int rechercheElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *element){
  ListeComposanteConnexe tmp = l;
  if(element == NULL) {
    return 0;
  }
  if(estVideListeComposanteConnexe(l)) {
    return 0;
  }
  while(!(estVideListeComposanteConnexe(tmp))){
    if(estIdentique(tmp->composantec, element)){
        return 1;
    }
  tmp = tmp->suivant;
  }
return 0;
}

ListeComposanteConnexe supprimeElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *element){
    ListeComposanteConnexe tmp = initListeComposanteConnexe();
    ListeComposanteConnexe save = initListeComposanteConnexe();
    save = l;
    if (rechercheElementListeComposanteConnexe(l,element)){

        if(l->composantec == element) {
            l = l->suivant;
            destructeurCelluleListeComposanteConnexe(save);
            save = NULL;
        }
        else {
            while (!estVideListeComposanteConnexe(l->suivant)){
                if(element == (l->suivant)->composantec){
                    tmp = l->suivant;
                    l->suivant = (l->suivant)->suivant;
                    destructeurCelluleListeComposanteConnexe(tmp);
                    tmp = NULL;
                }
                l = l->suivant;
            }
            l = save;
        }
    }
    return l;
}
