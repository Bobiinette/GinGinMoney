#ifndef COMPOSANTE_CONNEXE_H
#define COMPOSANTE_CONNEXE_H

/**
*/

typedef struct ComposanteConnexe ComposanteConnexe;

ComposanteConnexe initComposanteConnexe();
ComposanteConnexe constructeurComposanteConnexe(Case emplacementInitial, Case **grille);
void destructeurComposanteConnexe(ComposanteConnexe *cc);
ListeCase voisinsConnexes(Case emplacementInitial);
static int **tableauTestAppartenance(int taille);
static int grilleTeste(int **tab, int taille)
static void destructeurTableauTest(int **tab, int taille);
ListeComposanteConnexe ListeComposanteConnexeGrille(Case **grille, int tailleGrille);
int estIndentique(ComposanteConnexe cc1, ComposanteConnexe cc2);

#endif