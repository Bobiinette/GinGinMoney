#import "ComposanteConnexe.h"
#import "ListeComposanteConnexe.h"
#import "Grille.h"

/**
*/

struct ComposanteConnexe {
	Couleur couleur;
	ListeComposanteConnexe listeVoisins;
	ListeCase cases;
}

ComposanteConnexe initComposanteConnexe() {
	ComposanteConnexe res;
	res.couleur = 0;
	res.listeVoisins = initListeComposanteConnexe();/*Possiblement NULL*/
	res.cases = initListeCase();/*Possiblemet NULL*/
	return res;
}

ComposanteConnexe constructeurComposanteConnexe(Case emplacementInitial, Case **grille) {
	ComposanteConnexe res = initComposanteConnexe();
	res.couleur = getCouleurCase(emplacementInitial);
	ListeCase listeCasesPossibles = initListeCase();
	listeCasesPossibles = constructeurListeCase(&emplacementInitial, listeCasesPossibles);

	ListeCase aDetruire = NULL;
	ListeCase voisinsPossibles = NULL;
	do {
		aDetruire = listeCasesPossibles;
		listeCasesPossibles = getSuivantListeCase(listeCasesPossibles);
		res.cases = constructeurListeCase(*getValeurListeCase(aDetruire), res.cases);
		voisinsPossibles = voisinsConnexes(*getValeurListeCase(aDetruire), grille);

		destructeurCelluleListeCase(aDetruire);

		aDetruire = voisinsPossibles;
		
		while(voisinsPossibles != NULL) {
			if(!estPresentCaseDansListe(getValeurListeCase(voisinsPossibles), res.cases)) {
				listeCasesPossibles = constructeurListeCase(getValeurListeCase(voisinsPossibles), listeCasesPossibles);
			}
			voisinsPossibles = getSuivantListeCase(voisinsPossibles);
		}

		destructeurCelluleListeCase(aDetruire);		

	} while(!estVideListeCase(listeCasesPossibles));

	return res;
}

void destructeurComposanteConnexe(ComposanteConnexe *cc) {
	destructeurListeComposanteConnexe(cc->listeVoisins);
	destructeurListeCase(cc->listeCase);
	cc = NULL;
}

ListeCase voisinsConnexes(Case depart, Case **grille) {
	ListeCase res = initListeCase();

	if(getCouleurCase(grille[getXCase(depart) + 1][getYCase(depart)]) == getCouleurCase(emplacementInitial)) {
		res = constructeurListeCase(&grille[getXCase(depart) + 1][getYCase(depart)], res);
	}
	if(getCouleurCase(grille[getXCase(depart) - 1][getYCase(depart)]) == getCouleurCase(emplacementInitial)) {
		res = constructeurListeCase(&grille[getXCase(depart) - 1][getYCase(depart)], res);
	}
	if(getCouleurCase(grille[getXCase(depart)][getYCase(depart) + 1]) == getCouleurCase(emplacementInitial)) {
		res = constructeurListeCase(&grille[getXCase(depart)][getYCase(depart) + 1], res);
	}
	if(getCouleurCase(grille[getXCase(depart)][getYCase(depart)] - 1) == getCouleurCase(emplacementInitial)) {
		res = constructeurListeCase(&grille[getXCase(depart)][getYCase(depart) - 1], res);
	}

	return res;
}

static int **tableauTestAppartenance(int taille) {
	int i = 0;
	int **res = NULL;
	res = calloc(taille, sizeof(int*));

	for(i = 0; i < taille; i ++) {
		res[i] = calloc(taille, sizeof(int));
	}
	return res;
}

static int **completeGrilleTest(ListeCase aCompleter, int **grilleTest) {
	while(!estVideListeCase(aCompleter)) {
		grilleTest[getXCase(*getValeurListeCase(aCompleter))][getYCase(*getValeurListeCase(aCompleter))] = 1;
		aCompleter = getSuivantListeCase(aCompleter);
	}
	return grilleTest;
}

static void destructeurTableauTest(int **tab, int taille) {
	int i = 0;
	for(i = 0; i < taille; i++) {
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
}

ListeComposanteConnexe ListeComposanteConnexeGrille(Case **grille, int tailleGrille) {
	ListeComposanteConnexe res = NULL;
	int **tabTest = tableauTestAppartenance(tailleGrille);
	int i = 0;
	int j = 0;

	for(i = 0; i < tailleGrille; i ++) {
		for(j = 0; j < tailleGrille; j ++) {
			if(tabTest[i][j] == 0) {
				res = constructeurComposanteConnexe(grille[i][j], grille);
				tabTest = completeGrilleTest(res.cases, tabTest);
			}
		}
	}

	return res;
}

int estIndentique(ComposanteConnexe cc1, ComposanteConnexe cc2) {
	if(estVideListeCase(cc1.cases)) {
		return 0;
	}

	while(!estVideListeCase(cc1.cases)) {
		if(estVideListeCase(cc2.cases)) {
			return 0;
		}
		else {
			if(getXCase(*getValeurListeCase(cc1.cases))!=getXCase(*getValeurListeCase(cc2.cases))) {
				return 0;
			}
			if(getYCase(*getValeurListeCase(cc1.cases))!=getYCase(*getValeurListeCase(cc2.cases))) {
				return 0;
			}
		}
		cc1.cases = getSuivantListeCase(cc1.cases);
		cc2.cases = getSuivantListeCase(cc2.cases);
	}
	return 1;
}

