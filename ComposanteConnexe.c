#import "ComposanteConnexe.h"
#import "ListeComposanteConnexe.h"
#import "Grille.h"

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

static int grilleTeste(int **tab, int taille) {/* ça sert à rien lolooololololololol*/
	int i = 0;
	int j = 0;
	for(i = 0; i < taille; i ++) {
		for(j = 0; j < taille; j ++) {
			if(tab[i][j] == 0) {
				return 0;
			}
		}
	}
	return 1;
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
				/*ajout à liste composante connexe*/
			}
		}
	}
}