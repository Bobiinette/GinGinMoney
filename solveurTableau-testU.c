#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "solveurTableau3.h"

#define NB 20

int main()
{
	srand(time(NULL));
	Case **grille;
	TabComposanteConnexe tabCC = initTabComposanteConnexe();
	int nbrCoups = 0;
	char nbCoupsStr[100];
	Couleur couleur = H;
	ComposanteConnexe *cc = NULL;
	int i = 0, j = 0;
	double moyenne = 0.0;
	int a1 = 0, a2 = 0;
	FILE *f = fopen("./comparatifSolveurs.txt", "w+");

	fputs("Solveur force brute\t", f);
	fputs("Solveur heuristique\n", f);

	for(i = 5; i < 11; i ++) {
		fprintf(f, "Taille : %2d\n\n", i);
		for(j = 0; j < NB; j ++) {
			grille = tableauVide(i);
			grille = remplissageAleatoire(i, grille);
			tabCC = listeComposanteConnexeGrille(grille, i);
			tabCC = creeVoisins(tabCC, grille, i);
			cc = rechercheElementTabComposanteConnexeAvecCase(getCaseGrille(grille, 0, 0), tabCC);
			a1 = solveurTableau2(tabCC, cc);
			a2 = solveurTableau3(tabCC, cc);
			fprintf(f, "\t%3d\t\t%3d\n",a1 ,a2);
			moyenne = moyenne + a2 - a1;
			destructeurTabComposanteConnexe(tabCC);
			liberationGrille(grille, i);
		}
		moyenne = (double)moyenne / NB;
		fprintf(f, "Moyenne : %2.2lf Coups en plus.\n\n", moyenne);
		moyenne = 0.0;
	}
	fclose(f);
	return 0;
}