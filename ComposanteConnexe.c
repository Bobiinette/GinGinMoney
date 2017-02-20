#include <stdlib.h>

#include "ComposanteConnexe.h"

/**
*/

struct ComposanteConnexe {
	Couleur couleur;
	ListeComposanteConnexe listeVoisins;
	ListeCase cases;
};

ComposanteConnexe initComposanteConnexe() {
	ComposanteConnexe res;
	res.couleur = 0;
	res.listeVoisins = initListeComposanteConnexe();/*Possiblement NULL*/
	res.cases = initListeCase();/*Possiblemet NULL*/
	return res;
}

ComposanteConnexe constructeurComposanteConnexe(Case *emplacementInitial, Case ***grille) {/*Problèmes aux bord, manque int taille aeazurzrzuirifvbvfgaigvaeiogve*/
	ComposanteConnexe res = initComposanteConnexe();
	res.couleur = getCouleurCase(emplacementInitial);
	ListeCase listeCasesPossibles = initListeCase();
	listeCasesPossibles = constructeurListeCase(emplacementInitial, listeCasesPossibles);

	ListeCase aDetruire = initListeCase();
	ListeCase voisinsPossibles = initListeCase();
	do {
		aDetruire = listeCasesPossibles;
		listeCasesPossibles = getSuivantListeCase(listeCasesPossibles);
		res.cases = constructeurListeCase(getValeurListeCase(aDetruire), res.cases);
		voisinsPossibles = voisinsConnexes(getValeurListeCase(aDetruire), grille);

		destructeurCelluleListeCase(aDetruire);

		aDetruire = voisinsPossibles;
		
		while(!testListeCaseVide(voisinsPossibles)) {
			if(!estPresentDansListeCase(getValeurListeCase(voisinsPossibles), res.cases)) {
				listeCasesPossibles = constructeurListeCase(getValeurListeCase(voisinsPossibles), listeCasesPossibles);
			}
			voisinsPossibles = getSuivantListeCase(voisinsPossibles);
		}

		destructeurCelluleListeCase(aDetruire);		

	} while(!testListeCaseVide(listeCasesPossibles));

	return res;
}

void destructeurComposanteConnexe(ComposanteConnexe *cc) {
	if(cc != NULL) {
		if(!estVideListeComposanteConnexe(cc->listeVoisins)) {
			destructeurListeComposanteConnexe(cc->listeVoisins);
		}
		if(!testListeCaseVide(cc->cases)) {
			destructeurListeCase(cc->cases);
		}
	}
	cc = NULL;
}

ListeCase getCasesComposanteConnexe(ComposanteConnexe *cc) {
	return cc->cases;
}

ListeComposanteConnexe getComposantesVoisinesComposanteConnexe(ComposanteConnexe *cc) {
	return cc->listeVoisins;
}

Couleur getCouleurComposanteConnexe(ComposanteConnexe *cc) {
	return cc->couleur;
}

ListeCase voisinsConnexes(Case *depart, Case ***grille) {/*AAAaaaaaaaaaaaaaahhhhhhhhhh problèmes au bords*/
	ListeCase res = initListeCase();
	int x = 0;
	int y = 0;

	x = getXCase(depart);
	y = getYCase(depart);

	if(getCouleurCase(grille[x + 1][y]) == getCouleurCase(depart)) {
		res = constructeurListeCase(grille[x + 1][y], res);
	}
	if(getCouleurCase(grille[x - 1][y]) == getCouleurCase(depart)) {
		res = constructeurListeCase(grille[x - 1][y], res);
	}
	if(getCouleurCase(grille[x][y + 1]) == getCouleurCase(depart)) {
		res = constructeurListeCase(grille[x][y + 1], res);
	}
	if(getCouleurCase(grille[x][y - 1]) == getCouleurCase(depart)) {
		res = constructeurListeCase(grille[x][y - 1], res);
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
	while(!testListeCaseVide(aCompleter)) {
		grilleTest[getXCase(getValeurListeCase(aCompleter))][getYCase(getValeurListeCase(aCompleter))] = 1;
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

ListeComposanteConnexe listeComposanteConnexeGrille(Case ***grille, int tailleGrille) {
	ListeComposanteConnexe res = NULL;
	ComposanteConnexe cc = initComposanteConnexe();
	int **tabTest = tableauTestAppartenance(tailleGrille);
	int i = 0;
	int j = 0;

	for(i = 0; i < tailleGrille; i ++) {
		for(j = 0; j < tailleGrille; j ++) {
			if(tabTest[i][j] == 0) {
				cc = constructeurComposanteConnexe(grille[i][j], grille);
				res = constructeurListeComposanteConnexe(res, &cc);
				tabTest = completeGrilleTest(cc.cases, tabTest);
			}
		}
	}

	return res;
}

int estIdentique(ComposanteConnexe *cc1, ComposanteConnexe *cc2) {
	if(testListeCaseVide(cc1->cases)) {
		return 0;
	}

	while(!testListeCaseVide(cc1->cases)) {
		if(testListeCaseVide(cc2->cases)) {
			return 0;
		}
		else {
			if(getXCase(getValeurListeCase(cc1->cases))!=getXCase(getValeurListeCase(cc2->cases))) {
				return 0;
			}
			if(getYCase(getValeurListeCase(cc1->cases))!=getYCase(getValeurListeCase(cc2->cases))) {
				return 0;
			}
		}
		cc1->cases = getSuivantListeCase(cc1->cases);
		cc2->cases = getSuivantListeCase(cc2->cases);
	}
	return 1;
}

static ListeCase casesVoisines(ListeCase casesComposanteConnexe, Case ***grille) {
	ListeCase res = initListeCase();
	Case *tmp = NULL;
	int x = 0;
	int y = 0;
	while(!testListeCaseVide(casesComposanteConnexe)) {
		tmp = getValeurListeCase(casesComposanteConnexe);
		x = getXCase(tmp);
		y = getYCase(tmp);

		if(!estPresentDansListeCase(grille[x + 1][y], casesComposanteConnexe)) {
			res = constructeurListeCase(grille[x + 1][y], res);
		}
		if(!estPresentDansListeCase(grille[x - 1][y], casesComposanteConnexe)) {
			res = constructeurListeCase(grille[x - 1][y], res);
		}
		if(!estPresentDansListeCase(grille[x][y + 1], casesComposanteConnexe)) {
			res = constructeurListeCase(grille[x][y + 1], res);
		}
		if(!estPresentDansListeCase(grille[x][y - 1], casesComposanteConnexe)) {
			res = constructeurListeCase(grille[x][y - 1], res);
		}

		casesComposanteConnexe = getSuivantListeCase(casesComposanteConnexe);
	}
	return res;
}

static void supprimeCasesDansListe(ListeCase casesAEnlever, ListeCase *listeATronquer) {
	while(!testListeCaseVide(casesAEnlever)) {
		supprimeElementListeCase(getValeurListeCase(casesAEnlever), listeATronquer);
		casesAEnlever = getSuivantListeCase(casesAEnlever);
	}
}

ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, Case ***grille, TabComposanteConnexe tabCC) {
	ListeComposanteConnexe composantesVoisines = initListeComposanteConnexe();
	ListeCase casesVoisinesCC = initListeCase();
	ComposanteConnexe *cc = NULL;

	casesVoisinesCC = casesVoisines(casesComposanteConnexe, grille);

	while(!testListeCaseVide(casesVoisinesCC)) {
		cc = rechercheElementTabComposanteConnexeAvecCase(getValeurListeCase(casesVoisinesCC), tabCC);
		composantesVoisines = constructeurListeComposanteConnexe(composantesVoisines, cc);
		supprimeCasesDansListe(getValeurListeComposanteConnexe(composantesVoisines)->cases, &casesVoisinesCC);
		casesVoisinesCC = getSuivantListeCase(casesVoisinesCC);
	}

	return composantesVoisines;
}

ComposanteConnexe *changementCouleur(ComposanteConnexe *ccInitiale, TabComposanteConnexe *toutesComposantesConnexes, Couleur nouvelleCouleur) {
	ListeComposanteConnexe save = ccInitiale->listeVoisins;
	ccInitiale->couleur = nouvelleCouleur;
	ComposanteConnexe *tmp = NULL;
	ListeComposanteConnexe saveTmp = initListeComposanteConnexe();

	while(!estVideListeComposanteConnexe(ccInitiale->listeVoisins)) {
		tmp = getValeurListeComposanteConnexe(ccInitiale->listeVoisins);
		if(tmp->couleur == nouvelleCouleur) {
			ccInitiale->cases = concatenationListeCase(ccInitiale->cases, tmp->cases);
			tmp = rechercheElementTabComposanteConnexe(tmp, *toutesComposantesConnexes);
			saveTmp = tmp->listeVoisins;

			while(!estVideListeComposanteConnexe(tmp->listeVoisins)) { /*Tout ceci devient extrèmement bizarre, il va falloir commenter tout ça au plus vite*/
				if(rechercheElementListeComposanteConnexe(ccInitiale->listeVoisins, getValeurListeComposanteConnexe(tmp->listeVoisins)) == NULL) {
					ccInitiale->listeVoisins = constructeurListeComposanteConnexe(ccInitiale->listeVoisins, getValeurListeComposanteConnexe(tmp->listeVoisins));
				}
				tmp->listeVoisins = getSuivantListeComposanteConnexe(tmp->listeVoisins);
			}

			tmp->listeVoisins = saveTmp;
			supprimeElementTabComposanteConnexe(toutesComposantesConnexes, *tmp);
			ccInitiale->listeVoisins = getSuivantListeComposanteConnexe(ccInitiale->listeVoisins);
		}
	}
	ccInitiale->listeVoisins = save;
	return ccInitiale;
}

/*=====================================================Tab composante connexe==================================*/

struct t_CelluleTabComposanteConnexe {
	ComposanteConnexe composanteConnexe;
	struct t_CelluleTabComposanteConnexe *suivant;
};

TabComposanteConnexe initTabComposanteConnexe() {
	return NULL;
}

int estVideTabComposanteConnexe(TabComposanteConnexe tabCC) {
	return (tabCC == NULL);
}

TabComposanteConnexe constructeurTabComposanteConnexe(ComposanteConnexe cc, TabComposanteConnexe tabCC) {
	CelluleTabComposanteConnexe *cell;
 	cell=(CelluleTabComposanteConnexe *)malloc(sizeof(CelluleTabComposanteConnexe));
 	cell->composanteConnexe = cc;
 	cell->suivant = tabCC;
  return cell;
}

void destructeurCelluleTabComposanteConnexe(CelluleTabComposanteConnexe *cell) {
	destructeurComposanteConnexe(&(cell->composanteConnexe));
	free(cell);
}

void destructeurTabComposanteConnexe(TabComposanteConnexe tabCC) {
	TabComposanteConnexe tmp = initTabComposanteConnexe();
	while(!estVideTabComposanteConnexe(tabCC)) {
		tmp = tabCC;
		tabCC = tabCC->suivant;
		destructeurCelluleTabComposanteConnexe(tmp);
	}
}

int testVictoire(TabComposanteConnexe tabCC) {
	return (longueurTabComposanteConnexe(tabCC)==1);
}

int longueurTabComposanteConnexe(TabComposanteConnexe tabCC) {
	int longeur = 0;
	while (!estVideTabComposanteConnexe(tabCC)){
	  longeur = longeur + 1;
	  tabCC = tabCC->suivant;
	}
	return longeur;
}

void supprimeElementTabComposanteConnexe(TabComposanteConnexe *tabCC, ComposanteConnexe element) {
    TabComposanteConnexe tmp = initTabComposanteConnexe();
    TabComposanteConnexe save = initTabComposanteConnexe();
    save = *tabCC;

    if(estIdentique(&((*tabCC)->composanteConnexe), &element)) {
        *tabCC = (*tabCC)->suivant;
        destructeurCelluleTabComposanteConnexe(save);
    }
    else {
        while (!estVideTabComposanteConnexe((*tabCC)->suivant)){
            if(estIdentique(&element, &((*tabCC)->suivant)->composanteConnexe)){
                tmp = (*tabCC)->suivant;
                (*tabCC)->suivant = ((*tabCC)->suivant)->suivant;
                destructeurCelluleTabComposanteConnexe(tmp);
            }
            *tabCC = (*tabCC)->suivant;
        }
        *tabCC = save;
    }
}

static int estDansComposanteConnexe(Case *c, ComposanteConnexe cc) {
	return estPresentDansListeCase(c, cc.cases);
}

ComposanteConnexe *rechercheElementTabComposanteConnexeAvecCase(Case *c, TabComposanteConnexe tabCC) {
	ComposanteConnexe *cc = NULL;
	while(!estVideTabComposanteConnexe(tabCC)) {
		if(estDansComposanteConnexe(c, tabCC->composanteConnexe)) {
			cc = &(tabCC->composanteConnexe);
			return cc;
		}
	}
	return cc;
}

ComposanteConnexe *rechercheElementTabComposanteConnexe(ComposanteConnexe *cc, TabComposanteConnexe tabCC) {
	while(!estVideTabComposanteConnexe(tabCC)) {
		if(estIdentique(cc, &(tabCC->composanteConnexe))) {
			return &(tabCC->composanteConnexe);
		}
	}
	return NULL;
}

