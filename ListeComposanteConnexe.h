#ifndef LISTE_COMPOSANTE_CONNEXE_H
#define LISTE_COMPOSANTE_CONNEXE_H

typedef struct t_ListeComposanteConnexe CelluleComposanteConnexe;
typedef CelluleComposanteConnexe *ListeComposanteConnexe;

#include "ComposanteConnexe.h"

ListeComposanteConnexe initListeComposanteConnexe(void);
int estVideListeComposanteConnexe(ListeComposanteConnexe l);
ListeComposanteConnexe constructeurListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe c);
int longeurListeComposanteConnexe(ListeComposanteConnexe l);
int testVictoire(ListeComposanteConnexe l);
ComposanteConnexe getValeurListeComposanteConnexe(ListeComposanteConnexe l);
ListeComposanteConnexe getSuivantListeComposanteConnexe(ListeComposanteConnexe l);
void destructeurCelluleListeComposanteConnexe(CelluleComposanteConnexe *c);
void destructeurListeComposanteConnexe(ListeComposanteConnexe l);
ComposanteConnexe *rechercheElementListeComposanteConnexe(ListeComposanteConnexe l, ComposanteConnexe element);
void supprimeElementListeComposanteConnexe(ListeComposanteConnexe *l, ComposanteConnexe element);

#endif