#ifndef CASES_H
#define CASES_H

#include "Grille.h"

typedef struct t_listeCase CelluleCase;
typedef CelluleCase *ListeCase;

ListeCase initListeCase(void);

int testListeCaseVide(ListeCase l);

ListeCase constructeurListeCase(Case *d, ListeCase l);

Case* getValeurListeCase(ListeCase l);

ListeCase getSuivantListeCase(ListeCase l);

void destructeurCelluleListeCase(CelluleCase *c);

void destructeurListeCase(ListeCase l);

int estPresentDansListeCase(Case *c, ListeCase l);

ListeCase concatenationListeCase(ListeCase l, ListeCase m);

ListeCase supprimeElementListeCase(Case *c, ListeCase l);

int longueurListeCase(ListeCase l);

#endif
