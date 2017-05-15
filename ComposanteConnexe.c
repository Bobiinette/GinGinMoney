#include <stdlib.h>
#include <stdio.h>

#include "ComposanteConnexe.h"


struct ComposanteConnexe {
	Couleur couleur; /**< Couleur de la composante connexe*/
	ListeComposanteConnexe listeVoisins; /**< La liste des voisins de la composante connexe*/
	ListeCase cases; /**< La liste des cases qui composent la composantes connexes*/
};



ComposanteConnexe initComposanteConnexe() {
	ComposanteConnexe res;
	res.couleur = H;
	res.listeVoisins = initListeComposanteConnexe();
	res.cases = initListeCase();
	return res;
}


ComposanteConnexe constructeurComposanteConnexe(Case *emplacementInitial, Case **grille, int taille) {
	ComposanteConnexe res = initComposanteConnexe();
	res.couleur = getCouleurCase(emplacementInitial);
	ListeCase listeCasesPossibles = initListeCase();
	listeCasesPossibles = constructeurListeCase(emplacementInitial, listeCasesPossibles);

	ListeCase aDetruire = initListeCase();
	ListeCase voisinsPossibles = initListeCase();
	do {
		aDetruire = listeCasesPossibles;
		listeCasesPossibles = getSuivantListeCase(listeCasesPossibles);

		if(!estPresentDansListeCase(getValeurListeCase(aDetruire), res.cases)) { /*Il ne faut pas rajouter des cases déjà présentes dans la liste*/
			res.cases = constructeurListeCase(getValeurListeCase(aDetruire), res.cases);
		}

		voisinsPossibles = voisinsConnexes(getValeurListeCase(aDetruire), grille, taille);

		destructeurCelluleListeCase(aDetruire);

		aDetruire = voisinsPossibles;

		while(!testListeCaseVide(voisinsPossibles)) {
			if(!estPresentDansListeCase(getValeurListeCase(voisinsPossibles), res.cases)) {
				listeCasesPossibles = constructeurListeCase(getValeurListeCase(voisinsPossibles), listeCasesPossibles);
			}
			voisinsPossibles = getSuivantListeCase(voisinsPossibles);
		}

		destructeurListeCase(aDetruire);

	} while(!testListeCaseVide(listeCasesPossibles));
	return res;
}

ComposanteConnexe * creeComposanteConnexe(Case * emplacementInitial, Case **grille, int taille) {
	ComposanteConnexe *cc = NULL;
	cc = (ComposanteConnexe *)calloc(1, sizeof(ComposanteConnexe));
	*cc = constructeurComposanteConnexe(emplacementInitial, grille, taille);
	return cc;
}


void destructeurComposanteConnexe(ComposanteConnexe *cc) {
	if(cc != NULL) {
		if(!estVideListeComposanteConnexe(cc->listeVoisins)) {
			destructeurListeComposanteConnexe(cc->listeVoisins);
			cc->listeVoisins = NULL;
		}
		if(!testListeCaseVide(cc->cases)) {
			destructeurListeCase(cc->cases);
			cc->cases = NULL;
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

void setCouleurComposanteConnexe(ComposanteConnexe *cc, Couleur c){
	cc->couleur = c;
}

void setComposantesVoisinesComposanteConnexe(ComposanteConnexe *cc, ListeComposanteConnexe l){
	cc->listeVoisins = l;
}

void setCasesComposanteConnexe(ComposanteConnexe *cc,ListeCase lc){
	cc->cases = lc;
}


ListeCase voisinsConnexes(Case *depart, Case **grille, int taille) {
	ListeCase res = initListeCase();
	int x = 0;
	int y = 0;

	x = getXCase(depart);
	y = getYCase(depart);

	if(x < taille - 1 && getCouleurCase(getCaseGrille(grille, x + 1, y)) == getCouleurCase(depart)) {
		res = constructeurListeCase(getCaseGrille(grille, x + 1, y), res);
	}
	if(x > 0 && getCouleurCase(getCaseGrille(grille, x - 1, y)) == getCouleurCase(depart)) {
		res = constructeurListeCase(getCaseGrille(grille, x - 1, y), res);
	}
	if(y < taille - 1 && getCouleurCase(getCaseGrille(grille, x, y + 1)) == getCouleurCase(depart)) {
		res = constructeurListeCase(getCaseGrille(grille, x, y + 1), res);
	}
	if(y > 0 && getCouleurCase(getCaseGrille(grille, x, y - 1)) == getCouleurCase(depart)) {
		res = constructeurListeCase(getCaseGrille(grille, x, y - 1), res);
	}

	return res;
}


int **tableauTestAppartenance(int taille) {
	int i = 0;
	int **res = NULL;
	res = calloc(taille, sizeof(int*));

	for(i = 0; i < taille; i ++) {
		res[i] = calloc(taille, sizeof(int));
	}
	return res;
}


int **completeGrilleTest(ListeCase aCompleter, int **grilleTest) {
	while(!testListeCaseVide(aCompleter)) {
		grilleTest[getXCase(getValeurListeCase(aCompleter))][getYCase(getValeurListeCase(aCompleter))] = 1;
		aCompleter = getSuivantListeCase(aCompleter);
	}
	return grilleTest;
}


void destructeurTableauTest(int **tab, int taille) {
	int i = 0;
	for(i = 0; i < taille; i++) {
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
}


int estIdentique(ComposanteConnexe *cc1, ComposanteConnexe *cc2) {
	ListeCase cases1 = cc1->cases;
	ListeCase cases2 = cc2->cases;
	if(cc1 == NULL && cc2 == NULL) {
		return 1;
	}
	else if(cc1 != NULL && cc2 == NULL) {
		return 0;
	}
	else if(cc1 == NULL && cc2 != NULL) {
		return 0;
	}
	else if(testListeCaseVide(cases1) && !testListeCaseVide(cases2)) {
		return 0;
	}

	while(!testListeCaseVide(cases1)) {
		if(!estPresentDansListeCase(getValeurListeCase(cases1), cases2)) {
			return 0;
		}
		cases1 = getSuivantListeCase(cases1);
	}
	return 1;
}


int estVoisine(ComposanteConnexe *cc1, ComposanteConnexe *cc2) {
	if(cc1 == NULL || cc2 == NULL) {
		return 0;
	}
	else if(estVideListeComposanteConnexe(cc1->listeVoisins)) {
		return 0;
	}
	ListeComposanteConnexe tmp = cc1->listeVoisins;
	while(!estVideListeComposanteConnexe(tmp)) {
		if(getValeurListeComposanteConnexe(tmp) == cc2) {
			return 1;
		}
		tmp = getSuivantListeComposanteConnexe(tmp);
	}
	return 0;
}


ListeCase casesVoisines(ListeCase casesComposanteConnexe, Case **grille, int taille) {
	ListeCase res = initListeCase();
	Case *tmp = NULL;
	int x = 0;
	int y = 0;
	Couleur couleur = getCouleurCase(getValeurListeCase(casesComposanteConnexe));
	while(!testListeCaseVide(casesComposanteConnexe)) {
		tmp = getValeurListeCase(casesComposanteConnexe);
		x = getXCase(tmp);
		y = getYCase(tmp);

		if(x < taille - 1 && !estPresentDansListeCase(getCaseGrille(grille, x + 1, y), casesComposanteConnexe)) {
			if(!estPresentDansListeCase(getCaseGrille(grille, x + 1, y), res)) {
				if(getCouleurCase(getCaseGrille(grille, x + 1, y)) != couleur) {
					res = constructeurListeCase(getCaseGrille(grille, x + 1, y), res);
				}
			}
		}
		if(x > 0 && !estPresentDansListeCase(getCaseGrille(grille, x - 1, y), casesComposanteConnexe)) {
			if(!estPresentDansListeCase(getCaseGrille(grille, x - 1, y), res)) {
				if(getCouleurCase(getCaseGrille(grille, x - 1, y)) != couleur) {
					res = constructeurListeCase(getCaseGrille(grille, x - 1, y), res);
				}
			}
		}
		if(y < taille - 1 && !estPresentDansListeCase(getCaseGrille(grille, x, y + 1), casesComposanteConnexe)) {
			if(!estPresentDansListeCase(getCaseGrille(grille, x, y + 1), res)) {
				if(getCouleurCase(getCaseGrille(grille, x, y + 1)) != couleur) {
					res = constructeurListeCase(getCaseGrille(grille, x, y + 1), res);
				}
			}
		}
		if(y > 0 && !estPresentDansListeCase(getCaseGrille(grille, x, y - 1), casesComposanteConnexe)) {
			if(!estPresentDansListeCase(getCaseGrille(grille, x, y - 1), res)) {
				if(getCouleurCase(getCaseGrille(grille, x, y - 1)) != couleur) {
					res = constructeurListeCase(getCaseGrille(grille, x, y - 1), res);
				}
			}
		}

		casesComposanteConnexe = getSuivantListeCase(casesComposanteConnexe);
	}
	return res;
}


ListeCase supprimeCasesDansListe(ListeCase casesAEnlever, ListeCase listeATronquer) {
	int s = 0;
	while(!testListeCaseVide(casesAEnlever) && !testListeCaseVide(listeATronquer)) {
		listeATronquer = supprimeElementListeCase(getValeurListeCase(casesAEnlever), listeATronquer);
		casesAEnlever = getSuivantListeCase(casesAEnlever);
		s ++;
	}
	return listeATronquer;
}


ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, Case **grille, int taille, TabComposanteConnexe tabCC) {
	ListeComposanteConnexe composantesVoisines = initListeComposanteConnexe();
	ListeCase casesVoisinesCC = initListeCase();
	ComposanteConnexe *cc = NULL;
	ListeCase aDetruire = initListeCase();

	casesVoisinesCC = casesVoisines(casesComposanteConnexe, grille, taille);
	aDetruire = casesVoisinesCC;

	while(!testListeCaseVide(casesVoisinesCC)) {
		cc = rechercheElementTabComposanteConnexeAvecCase(getValeurListeCase(casesVoisinesCC), tabCC);
		composantesVoisines = constructeurListeComposanteConnexe(composantesVoisines, cc);
		casesVoisinesCC = supprimeCasesDansListe(cc->cases, casesVoisinesCC);
	}
	return composantesVoisines;
}

void changementCouleurCase(ComposanteConnexe *cc, Couleur couleur) {
	ListeCase tmp = cc->cases;
	while(!testListeCaseVide(cc->cases)) {
		setCouleur(getValeurListeCase(cc->cases), couleur);
		cc->cases = getSuivantListeCase(cc->cases);
	}
	cc->cases = tmp;
}


ComposanteConnexe *changementCouleur(ComposanteConnexe *ccInitiale, TabComposanteConnexe *toutesComposantesConnexes, Couleur nouvelleCouleur) {
	if(ccInitiale == NULL) {
		printf("Impossible de changer la couleur de NULL");
		return NULL;
	}
	else if(ccInitiale->couleur == nouvelleCouleur) {
		/*printf("Impossible de changer la couleur, la couleur est la même qu'à l'origine\n");*/
		return ccInitiale;
	}
	ListeComposanteConnexe aParcourir = ccInitiale->listeVoisins;
	ccInitiale->couleur = nouvelleCouleur;
	ComposanteConnexe *tmp = NULL;
	ComposanteConnexe *tmp2 = NULL; /*juste pour stocker getValeurListeComposanteConnexe(tmp->listeVoisins) et améliorer la lisibilité*/
	ListeComposanteConnexe voisinsBonneCouleur = initListeComposanteConnexe();
	ListeComposanteConnexe save = initListeComposanteConnexe();
	ListeComposanteConnexe voisinsEltSelectionne = initListeComposanteConnexe();
	ListeComposanteConnexe nouveauxVoisins = initListeComposanteConnexe();
	changementCouleurCase(ccInitiale, nouvelleCouleur);

	/*D'abord on regarde les omposantes connexes voisines de la bonne couleur*/
	while(!estVideListeComposanteConnexe(aParcourir)) {
		tmp = getValeurListeComposanteConnexe(aParcourir);
		if(tmp->couleur == nouvelleCouleur) {
			ccInitiale->cases = concatenationListeCase(ccInitiale->cases, tmp->cases);
			tmp->cases = NULL;
			voisinsBonneCouleur = constructeurListeComposanteConnexe(voisinsBonneCouleur, tmp);

			tmp->couleur = H;
		}
		/*Si la composante connexe n'est pas de la bonne couleur, on la remet dans les voisins*/
		else if(tmp->couleur != H) {
			nouveauxVoisins = constructeurListeComposanteConnexe(nouveauxVoisins, tmp);
		}
		aParcourir = getSuivantListeComposanteConnexe(aParcourir);
		tmp = NULL;
	}
	save = voisinsBonneCouleur;

	/*Puis on ajoute les voisins des composantes connexes voisines de la bonne couleur aux voisins de ccInitiale*/
	while(!estVideListeComposanteConnexe(voisinsBonneCouleur)) {
		voisinsEltSelectionne = getValeurListeComposanteConnexe(voisinsBonneCouleur)->listeVoisins;

		while(!estVideListeComposanteConnexe(voisinsEltSelectionne)) {
			tmp2 = getValeurListeComposanteConnexe(voisinsEltSelectionne);

			if(!estPresentElementTabComposanteConnexe(tmp2, *toutesComposantesConnexes)) {
				tmp2 = NULL;
			}

			if(tmp2 != NULL) {
				if(tmp2->couleur != H) {
					if(tmp2->couleur != nouvelleCouleur && !rechercheElementListeComposanteConnexe(nouveauxVoisins, tmp2)) {
						nouveauxVoisins = constructeurListeComposanteConnexe(nouveauxVoisins, tmp2);
					}
				}
			}
			voisinsEltSelectionne = getSuivantListeComposanteConnexe(voisinsEltSelectionne);
		}
		voisinsBonneCouleur = getSuivantListeComposanteConnexe(voisinsBonneCouleur);
	}
	destructeurListeComposanteConnexe(save);
	save = NULL;
	destructeurListeComposanteConnexe(ccInitiale->listeVoisins);
	ccInitiale->listeVoisins = NULL;
	*toutesComposantesConnexes = supprimeElementTabComposanteConnexe(*toutesComposantesConnexes);
	ccInitiale->listeVoisins = nouveauxVoisins;
	return ccInitiale;
}

/*=====================================================Tab composante connexe==================================*/


struct t_CelluleTabComposanteConnexe {
	ComposanteConnexe composanteConnexe; /**< ComposanteConnexe de la tête de la liste.*/
	struct t_CelluleTabComposanteConnexe *suivant; /**< Pointeur vers le suivant de la liste*/
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

TabComposanteConnexe constructeurTabComposanteConnexep(ComposanteConnexe *cc, TabComposanteConnexe tabCC) {
	CelluleTabComposanteConnexe *cell;
 	cell=(CelluleTabComposanteConnexe *)malloc(sizeof(CelluleTabComposanteConnexe));
 	cell->composanteConnexe = *cc;
 	cell->suivant = tabCC;
  return cell;
}


ComposanteConnexe * getValeurTabComposanteConnexe(TabComposanteConnexe tabCC) {
	return &(tabCC->composanteConnexe);
}


TabComposanteConnexe getSuivantTabComposanteConnexe(TabComposanteConnexe tabCC) {
	return tabCC->suivant;
}


void destructeurCelluleTabComposanteConnexe(CelluleTabComposanteConnexe *cell) {
	destructeurComposanteConnexe(&(cell->composanteConnexe));
	free(cell);
	cell = NULL;
}


void destructeurTabComposanteConnexe(TabComposanteConnexe tabCC) {
	TabComposanteConnexe tmp = initTabComposanteConnexe();
	while(!estVideTabComposanteConnexe(tabCC)) {
		tmp = tabCC;
		tabCC = tabCC->suivant;
		destructeurCelluleTabComposanteConnexe(tmp);
	}
}


TabComposanteConnexe listeComposanteConnexeGrille(Case **grille, int tailleGrille) {
	TabComposanteConnexe res = NULL;
	ComposanteConnexe cc = initComposanteConnexe();
	int **tabTest = tableauTestAppartenance(tailleGrille);
	int i = 0;
	int j = 0;

	for(i = 0; i < tailleGrille; i ++) {
		for(j = 0; j < tailleGrille; j ++) {
			if(tabTest[i][j] == 0) {
				cc = constructeurComposanteConnexe(getCaseGrille(grille, i, j), grille, tailleGrille);
				res = constructeurTabComposanteConnexe(cc, res);
				tabTest = completeGrilleTest(cc.cases, tabTest);
			}
		}
	}

	destructeurTableauTest(tabTest, tailleGrille);

	return res;
}


TabComposanteConnexe creeVoisins(TabComposanteConnexe tabCC, Case **grille, int taille) {
	TabComposanteConnexe save = tabCC;
	while(!estVideTabComposanteConnexe(tabCC)) {
		(tabCC->composanteConnexe).listeVoisins = definieComposantesConnexesVoisines((tabCC->composanteConnexe).cases, grille, taille, save);
		tabCC = tabCC->suivant;
	}
	tabCC = save;
	return tabCC;
}


int testVictoire(TabComposanteConnexe tabCC, ComposanteConnexe *cc) {
	if(longueurTabComposanteConnexe(tabCC)==1) {
		return 1;
	}
	if(longueurListeComposanteConnexe(cc->listeVoisins) == 0) {
		return 1;
	}
	return 0;
}


int longueurTabComposanteConnexe(TabComposanteConnexe tabCC) {
	int longeur = 0;
	while (!estVideTabComposanteConnexe(tabCC)){
	  longeur = longeur + 1;
	  tabCC = tabCC->suivant;
	}
	return longeur;
}


TabComposanteConnexe supprimeElementTabComposanteConnexe(TabComposanteConnexe tabCC) {
    TabComposanteConnexe tmp = initTabComposanteConnexe();
    TabComposanteConnexe save = initTabComposanteConnexe();
    save = tabCC;

     if(testListeCaseVide((tabCC->composanteConnexe).cases) || (tabCC->composanteConnexe).couleur == H){
        tmp = tabCC;
        tabCC = tabCC->suivant;
        destructeurCelluleTabComposanteConnexe(tmp);
        tmp = NULL;
        return tabCC;
    }
    while (!estVideTabComposanteConnexe(tabCC->suivant)){
        if(testListeCaseVide(((tabCC->suivant)->composanteConnexe).cases) || ((tabCC->suivant)->composanteConnexe).cases == H){
            tmp = tabCC->suivant;
            if(tabCC->suivant != NULL) {
            	tabCC->suivant = (tabCC->suivant)->suivant;
            }

            destructeurCelluleTabComposanteConnexe(tmp);
            tmp = NULL;
        }
        tabCC = tabCC->suivant;
    }
    tabCC = save;
    return tabCC;
}


int estDansComposanteConnexe(Case *c, ComposanteConnexe cc) {
	return estPresentDansListeCase(c, cc.cases);
}


ComposanteConnexe *rechercheElementTabComposanteConnexeAvecCase(Case *c, TabComposanteConnexe tabCC) {
	ComposanteConnexe *cc = NULL;
	while(!estVideTabComposanteConnexe(tabCC)) {
		if(estDansComposanteConnexe(c, tabCC->composanteConnexe)) {
			cc = &(tabCC->composanteConnexe);
			return cc;
		}
		tabCC = tabCC->suivant;
	}
	return cc;
}


int estPresentElementTabComposanteConnexe(ComposanteConnexe *cc, TabComposanteConnexe tabCC) {
	while(!estVideTabComposanteConnexe(tabCC)) {
		if(cc == &(tabCC->composanteConnexe)) {
			return 1;
		}
		tabCC = tabCC->suivant;
	}
	return 0;
}


int rangTabComposanteConnexe(ComposanteConnexe *cc, TabComposanteConnexe tabCC) {
	int rang = 0;
	TabComposanteConnexe tmp = tabCC;
	if(cc == NULL) {
		return -1;
	}
	while(!estVideTabComposanteConnexe(tabCC)) {
		if(cc == &(tabCC->composanteConnexe)) {
			tabCC = tmp;
			return rang;
		}
		rang ++;
		tabCC = tabCC->suivant;
	}
	tabCC = tmp;
	return -1;
}
