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
	if(cc != NULL) {
		if(!estVideListeCase(cc->listeVoisins)) {
			destructeurListeComposanteConnexe(cc->listeVoisins);
		}
		if(!estVideListeComposanteConnexe(cc->listeCase)) {
			destructeurListeCase(cc->listeCase);
		}
	}
	cc = NULL;
}

ListeCase getCasesComposanteConnexe(ComposanteConnexe cc) {
	return cc.cases;
}

ListeComposanteConnexe getComposantesVoisinesComposanteConnexe(ComposanteConnexe cc) {
	return cc.listeVoisins;
}

Couleur getCouleurComposanteConnexe(ComposanteConnexe cc) {
	return cc.couleur;
}

ListeCase voisinsConnexes(Case depart, Case **grille) {
	ListeCase res = initListeCase();
	int x = 0;
	int y = 0;

	x = getXCase(depart);
	y = getYCase(depart);

	if(getCouleurCase(grille[x + 1][y]) == getCouleurCase(emplacementInitial)) {
		res = constructeurListeCase(&grille[x + 1][y], res);
	}
	if(getCouleurCase(grille[x - 1][y]) == getCouleurCase(emplacementInitial)) {
		res = constructeurListeCase(&grille[x - 1][y], res);
	}
	if(getCouleurCase(grille[x][y + 1]) == getCouleurCase(emplacementInitial)) {
		res = constructeurListeCase(&grille[x][y + 1], res);
	}
	if(getCouleurCase(grille[x][y] - 1) == getCouleurCase(emplacementInitial)) {
		res = constructeurListeCase(&grille[x][y - 1], res);
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

ListeComposanteConnexe listeComposanteConnexeGrille(Case **grille, int tailleGrille) {
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

static ListeCase casesVoisines(ListeCase casesComposanteConnexe, Case **grille) {
	ListeCase res = initListeCase();
	Case *tmp = NULL;
	int x = 0;
	int y = 0;
	while(!estVideListeCase(casesComposanteConnexe)) {
		tmp = getValeurListeCase(casesComposanteConnexe);
		x = getXCase(*tmp);
		y = getYCase(*tmp);

		if(!estPresentCaseDansListe(&grille[x + 1][y], casesComposanteConnexe)) {
			res = constructeurListeCase(&grille[x + 1][y], res);
		}
		if(!estPresentCaseDansListe(&grille[x - 1][y], casesComposanteConnexe)) {
			res = constructeurListeCase(&grille[x - 1][y], res);
		}
		if(!estPresentCaseDansListe(&grille[x][y + 1], casesComposanteConnexe)) {
			res = constructeurListeCase(&grille[x][y + 1], res);
		}
		if(!estPresentCaseDansListe(&grille[x][y - 1], casesComposanteConnexe)) {
			res = constructeurListeCase(&grille[x][y - 1], res);
		}

		casesComposanteConnexe = getSuivantListeCase(casesComposanteConnexe);
	}
	return res;
}

static void supprimeCasesDansListe(listeCase casesAEnlever, listeCase *listeATronquer) {
	while(!estVideListeCase(casesAEnlever)) {
		supprimeElementListeCase(getValeurListeCase(casesAEnlever), *listeATronquer);
		casesAEnlever = getSuivantListeCase(casesAEnlever);
	}
}

ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, Case **grille) {
	ListeComposanteConnexe composantesVoisines = initListeComposanteConnexe();
	ListeCase casesVoisines = initListeCase();

	casesVoisines = casesVoisines(casesComposanteConnexe, grille);

	while(!estVideListeCase(casesVoisines)) {
		composantesVoisines = constructeurListeComposanteConnexe(constructeurComposanteConnexe(*getValeurListeCase(casesVoisines)), composantesVoisines);
		supprimeCasesDansListe(composantesVoisines.cases, &casesVoisines);
		casesVoisines = getSuivantListeCase(casesVoisines);
	}

	return composantesVoisines;
}

ComposanteConnexe changementCouleur(ComposanteConnexe ccInitiale, ListeComposanteConnexe *toutesComposantesConnexes, Couleur nouvelleCouleur) {
	ccInitiale.couleur = nouvelleCouleur;
	ComposanteConnexe tmp = initComposanteConnexe();

	while(!estVideListeComposanteConnexe(ccInitiale.listeVoisins)) {
		tmp = getValeurListeComposanteConnexe(cc.listeVoisins);
		if(tmp.couleur == nouvelleCouleur) {
			ccInitiale.listeCase = concatenationListeCase(ccInitiale.listeCase, tmp.cases);
			tmp =*rechercheComposanteConnexe(tmp, *toutesComposantesConnexes);

			while(!estVideListeComposanteConnexe(tmp.listeVoisins)) { /*Tout ceci devient extrèmement bizarre, il va falloir commenter tout ça au plus vite*/
				if(!estPresentComposanteConnexe(getValeurListeComposanteConnexe(tmp.listeVoisins)), ccInitiale.listeVoisins) {
					ccInitiale.listeVoisins = constructeurListeComposanteConnexe(getValeurListeComposanteConnexe(tmp.listeVoisins), ccInitiale.listeVoisins);
				}
			}

			supprimeElementListeComposanteConnexe(tmp, *toutesComposantesConnexes);
		}
	}
	return ccInitiale;
}