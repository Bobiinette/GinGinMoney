#ifndef SOLVEUR_H
#define SOLVEUR_H

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
int longueurListeInt(ListeInt l);
ListeInt **creeTabVoisins(TabComposanteConnexe tabCC, int taille);
void detruitTabVoisins(ListeInt **tab, int taille);
ListeInt **changementCouleurSolveur(ListeInt **tabVoisins, int taille, int* nouvelleTaille, Couleur nouvelleCouleur);
ListeInt additionScalaireListeInt(ListeInt l, int n);
ListeInt triListeInt(ListeInt l);
ListeInt **supprimeColone(ListeInt **tabVoisins, int taille, int nouvelleTaille, ListeInt colonesAEnlever);
void solveurEtape(ListeInt **tabVoisins, int taille, int *tailleMax, FILE **f, char *str, int nbrCoups);
void solveur(TabComposanteConnexe tabCC, ComposanteConnexe *cc);

#endif