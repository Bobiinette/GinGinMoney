#ifndef COMPOSANTE_CONNEXE_H
#define COMPOSANTE_CONNEXE_H

/**
*/

typedef struct ComposanteConnexe ComposanteConnexe;

ComposanteConnexe initComposanteConnexe();
ComposanteConnexe constructeurComposanteConnexe(Case emplacementInitial, Case **grille);
void destructeurComposanteConnexe(ComposanteConnexe *cc);
ListeCase getCasesComposanteConnexe(ComposanteConnexe cc);
ListeComposanteConnexe getComposantesVoisinesComposanteConnexe(ComposanteConnexe cc);
Couleur getCouleurComposanteConnexe(ComposanteConnexe cc);

ListeCase voisinsConnexes(Case emplacementInitial);
static int **tableauTestAppartenance(int taille);
static int grilleTeste(int **tab, int taille);
static void destructeurTableauTest(int **tab, int taille);
ListeComposanteConnexe listeComposanteConnexeGrille(Case **grille, int tailleGrille);
int estIndentique(ComposanteConnexe cc1, ComposanteConnexe cc2);
static ListeCase casesVoisines(ListeCase casesComposanteConnexe, Case **grille);
static void supprimeCasesDansListe(listeCase casesAEnlever, listeCase *listeATronquer) ;
ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, ListeComposanteConnexe listeCC, Case **grille);

#endif