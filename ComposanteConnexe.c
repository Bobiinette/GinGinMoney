#import "ComposanteConnexe.h"
#import "Grille.h"

struct ComposanteConnexe {
	Couleur couleur;
	ListeComposanteConnexe listeVoisins;
	ListeCase cases;
}

ComposanteConnexe constructeurComposanteConnexe(Case emplacementInitial) {
	ComposanteConnexe res = NULL;
	res.couleur = emplacementInitial.couleur;
	ListeCase listeCasesPossibles = NULL;
	listeCasesPossibles = constructeurListeCase(emplacementInitial);
	ComposanteConnexe.cases = constructeurListeCase(emplacementInitial);
	do {
		Case tmp = listeCasesPossibles->(*valeur);
		
		destructeurCelluleListeCase()
	}
}