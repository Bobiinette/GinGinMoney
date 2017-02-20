#include <stdlib.h>

#include "ListeComposanteConnexe.h"

typedef struct t_ListeComposanteConnexe{
    ComposanteConnexe *composantec;
    struct t_ListeComposanteConnexe *suivant;
};

ListeComposanteConnexe initListeComposanteConnexe(void){
    return NULL;
}

int estVideListeComposanteConnexe(ListeComposanteConnexe l){
    return (l==NULL);
}

ComposanteConnexe* getValeurListeComposanteConnexe(ListeComposanteConnexe l){
    return l->composantec;
}

ListeComposanteConnexe getSuivantListeComposanteConnexe(ListeComposanteConnexe l){
    return l->suivant;
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
}

void destructeurListeComposanteConnexe(ListeComposanteConnexe l){
    ListeComposanteConnexe tmp;
    while (!estVideListeComposanteConnexe(l)){
        tmp = l;
        l = l->suivant;
        destructeurCelluleListeComposanteConnexe(tmp);
    }
}

int longeurListeComposanteConnexe(ListeComposanteConnexe l){
	int longeur=0;
    while (!estVideListeComposanteConnexe(l)){
        longeur=longeur+1;
        l=l->suivant;
    }
    return longeur;
}

ComposanteConnexe *rechercheElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe *element){
    while(!(estVideListeComposanteConnexe(l))){
        if(estIdentique(element,l->composantec)){
            return l->composantec;
        }
        l=l->suivant;
    }
    return NULL;
}

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
