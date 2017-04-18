#ifndef SOLVEUR_TABLEAU_H
#define SOLVEUR_TABLEAU_H

#include "ComposanteConnexe.h"
#include "Grille.h"

typedef struct t_CelluleListeInt CelluleListeInt;
typedef CelluleListeInt *ListeInt;

typedef struct t_CelluleListeVerif CelluleListeVerif;
typedef CelluleListeVerif *ListeVerif;

ListeInt initListeInt();
ListeInt constructeurListeInt(int v, ListeInt l);
void destructeurCelluleListeInt(CelluleListeInt *c);
void destructeurListeInt(ListeInt l);
int estPresentDansListeInt(int v, ListeInt l);
ListeInt concatenationListeInt(ListeInt l1, ListeInt l2);
ListeInt concatenationListeIntDecalage(ListeInt l1, ListeInt l2, int *decalage);
int longueurListeInt(ListeInt l);

ListeVerif constructeurListeVerif(int *v, int t, ListeVerif l);
void destructeurCelluleListeVerif(CelluleListeVerif *c);
void destructeurListeVerif(ListeVerif l);
int estEgal(char *c1, char *c2, int taille);
int estPresentDansListeVerif(int *v, int taille, ListeVerif l);

ListeInt **creeTabVoisins(TabComposanteConnexe tabCC, int taille);
void detruitTabVoisins(ListeInt **tab, int taille);
ListeInt **miseAjourCC(ListeInt **ccInitiale, const int taille, int a);
int **miseAzero(int **deplacement, const int taille, int a);
int *copieTabInt(int *deplacement, const int taille);
int nombreVoisinsNonNull(ListeInt *ccPrincipale);
ListeInt **changementCouleurSolveur(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **deplacement, const int taille, int couleur, int nombreCoups);
void solveurEtape(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **deplacement, int taille, int *tailleMax, FILE **f, char *str, int nbrCoups);
void solveur(TabComposanteConnexe tabCC, ComposanteConnexe *cc);

#endif