#ifndef SOLVEUR_TABLEAU_H
#define SOLVEUR_TABLEAU_H

#include "ComposanteConnexe.h"
#include "Grille.h"

typedef struct t_CelluleListeInt CelluleListeInt;
typedef CelluleListeInt *ListeInt;

ListeInt initListeInt();
ListeInt constructeurListeInt(int v, ListeInt l);
void destructeurCelluleListeInt(CelluleListeInt *c);
void destructeurListeInt(ListeInt l);
int estPresentDansListeInt(int v, ListeInt l);
ListeInt concatenationListeInt(ListeInt l1, ListeInt l2);
ListeInt concatenationListeIntDecalage(ListeInt l1, ListeInt l2, int *decalage);
int longueurListeInt(ListeInt l);
ListeInt **creeTabVoisins(TabComposanteConnexe tabCC, int taille);
void detruitTabVoisins(ListeInt **tab, int taille);
int *copieTabInt(int *deplacement, const int taille);
int nombreVoisinsNonNull(ListeInt *ccPrincipale);
ListeInt *changementCouleurSolveur(ListeInt **tabVoisins, ListeInt *ccPrincipale, int *deplacement, const int taille, int couleur);
void solveurEtape(ListeInt **tabVoisins, ListeInt *ccPrincipale, int *deplacement, int taille, int *tailleMax, FILE **f, char *str, int nbrCoups);
void solveur(TabComposanteConnexe tabCC, ComposanteConnexe *cc);

#endif