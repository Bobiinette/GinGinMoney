#ifndef COMPOSANTE_CONNEXE_H
#define COMPOSANTE_CONNEXE_H

typedef struct ComposanteConnexe ComposanteConnexe;
typedef struct t_CelluleTabComposanteConnexe CelluleTabComposanteConnexe;
typedef CelluleTabComposanteConnexe *TabComposanteConnexe;

#include "ListeComposanteConnexe.h"
#include "Grille.h"
#include "Cases.h"
/**
*/

static ComposanteConnexe initComposanteConnexe();
static ComposanteConnexe constructeurComposanteConnexe(Case *emplacementInitial, Case **grille, int taille);
ComposanteConnexe * creeComposanteConnexe(Case * emplacementInitial, Case **grille, int taille); /*Juste pour les testsU*/
void destructeurComposanteConnexe(ComposanteConnexe *cc);
ListeCase getCasesComposanteConnexe(ComposanteConnexe *cc);
ListeComposanteConnexe getComposantesVoisinesComposanteConnexe(ComposanteConnexe *cc);
Couleur getCouleurComposanteConnexe(ComposanteConnexe *cc);

ListeCase voisinsConnexes(Case *depart, Case **grille, int taille);
static int **tableauTestAppartenance(int taille);
static int grilleTeste(int **tab, int taille);
static void destructeurTableauTest(int **tab, int taille);
int estIdentique(ComposanteConnexe *cc1, ComposanteConnexe *cc2);
static ListeCase casesVoisines(ListeCase casesComposanteConnexe, Case **grille, int taille);
static ListeCase supprimeCasesDansListe(ListeCase casesAEnlever, ListeCase listeATronquer);
static ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, Case **grille, int taille, TabComposanteConnexe tabCC);
ComposanteConnexe *changementCouleur(ComposanteConnexe *ccInitiale, TabComposanteConnexe *toutesComposantesConnexes, Couleur nouvelleCouleur);

/*======================================================Tab composante connexe=============================================*/

TabComposanteConnexe initTabComposanteConnexe();
int estVideTabComposanteConnexe(TabComposanteConnexe tabCC);
TabComposanteConnexe constructeurTabComposanteConnexe(ComposanteConnexe cc, TabComposanteConnexe tabCC);
ComposanteConnexe * getValeurTabComposanteConnexe(TabComposanteConnexe tabCC);
TabComposanteConnexe getSuivantTabComposanteConnexe(TabComposanteConnexe tabCC);
void destructeurCelluleTabComposanteConnexe(CelluleTabComposanteConnexe *cell);
void destructeurTabComposanteConnexe(TabComposanteConnexe tabCC);

TabComposanteConnexe listeComposanteConnexeGrille(Case **grille, int tailleGrille);
TabComposanteConnexe creeVoisins(TabComposanteConnexe tabCC, Case **grille, int taille);
int testVictoire(TabComposanteConnexe tabCC);
int longueurTabComposanteConnexe(TabComposanteConnexe tabCC);
void supprimeElementTabComposanteConnexe(TabComposanteConnexe *tabCC, ComposanteConnexe element);
static int estDansComposanteConnexe(Case *c, ComposanteConnexe cc);
ComposanteConnexe *rechercheElementTabComposanteConnexeAvecCase(Case *c, TabComposanteConnexe tabCC);
ComposanteConnexe *rechercheElementTabComposanteConnexe(ComposanteConnexe *cc, TabComposanteConnexe tabCC);

#endif
