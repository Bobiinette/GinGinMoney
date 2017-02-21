#include <stdlib.h>

#include "ComposanteConnexe.h"

/**\file ComposanteConnexe.c
 *\brief Gestion des composantes connexes.
 *		Module permettant la gestion des composantes connexes, et d'une liste de composante connexe (sans pointeurs).
 */

/**\struct ComposanteConnexe ComposanteConnexe.h
 *\brief Structure de composante connexe.
 */

struct ComposanteConnexe {
	Couleur couleur; /**< Couleur de la composante connexe*/
	ListeComposanteConnexe listeVoisins; /**< La liste des voisins de la composante connexe*/
	ListeCase cases; /**< La liste des cases qui composent la composantes connexes*/
};

/**\fn CompoanteConnexe initComposanteConnexe (void)
 *\brief Initialise une composante connexe à NULL
 *\param void
 *\return ComposanteConnexe initialisée à NULL, et couleur bleu
 */

ComposanteConnexe initComposanteConnexe() {
	ComposanteConnexe res;
	res.couleur = B;
	res.listeVoisins = initListeComposanteConnexe();
	res.cases = initListeCase();
	return res;
}

/**\fn ComposanteConnexe constructeurComposanteConnexe(Case *emplacementInitial, Case ***grille, int taille)
 *\brief Constructeur d'une composante connexe. Permet de créer une composante connxe à partir d'une case et de la grille. Ne crée pas la liste des voisins de la composante connexe.
 *		Voir aussi voisinsConnexes().
 *\param emplacementInitial Pointeur vers la case à partir de laquelle on veut créer une composante connexe.
 *\param grille Pointeur vers la grille de jeu. La grille doit-être non NULL.
 *\param taille Taille de la grille de jeu.
 *\return ComposanteConnexe initialisée avec ses cases et sa couleur, mais pas ses composantes connexes voisines.
 */

ComposanteConnexe constructeurComposanteConnexe(Case *emplacementInitial, Case ***grille, int taille) {
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
		voisinsPossibles = voisinsConnexes(getValeurListeCase(aDetruire), grille, taille);

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

/**\fn void destructeurComposanteConnexe(ComposanteConnexe *cc)
 *\brief Destructeur d'une composante connexe, libère la mémoire.
 *\param cc Pointeur vers la composante connexe à détruire.
 *\return void
 */

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

/**\fn ListeCase getCasesComposanteConnexe(ComposanteConnexe *cc)
 *\brief Getter pour obtenir les cases qui composent la composante connexe.
 *\param cc La composante dont on veut la liste des cases qui la compose.
 *\return La liste des cases qui composent la composante connexe.
 */

ListeCase getCasesComposanteConnexe(ComposanteConnexe *cc) {
	return cc->cases;
}

/**\fn ListeComposanteConnexe getComposantesVoisinesComposanteConnexe(ComposanteConnexe *cc)
 *\brief Getter pour obtenir les voisins de la composante connexe.
 *\param cc La composante dont on veut la liste des voisins.
 *\return La liste des voisins la composante connexe.
 */

ListeComposanteConnexe getComposantesVoisinesComposanteConnexe(ComposanteConnexe *cc) {
	return cc->listeVoisins;
}

/**\fn Couleur getCouleurComposanteConnexe(ComposanteConnexe *cc)
 *\brief Getter pour obtenir la couleur de la composante connexe.
 *\param cc La composante dont on veut la couleur.
 *\return La couleur de la composante connexe.
 */

Couleur getCouleurComposanteConnexe(ComposanteConnexe *cc) {
	return cc->couleur;
}

/**\fn ListeCase voisinsConnexes(Case *depart, Case ***grille, int taille)
 *\brief Fonction pour obtenir la liste de toutes les cases voisines de même couleur d'une case passée en paramètre.
 *\param depart Pointeur vers la case dont ont veut toutes les cases voisines de même couleur.
 *\param grille Pointeur vers la grille de jeu, non NULL.
 *\param taille La taille de la grille de jeu.
 *\return La liste des cases voisines de la case depart de même couleur.
 */

ListeCase voisinsConnexes(Case *depart, Case ***grille, int taille) {
	ListeCase res = initListeCase();
	int x = 0;
	int y = 0;

	x = getXCase(depart);
	y = getYCase(depart);

	if(x < taille && getCouleurCase(grille[x + 1][y]) == getCouleurCase(depart)) {
		res = constructeurListeCase(grille[x + 1][y], res);
	}
	if(x > 0 && getCouleurCase(grille[x - 1][y]) == getCouleurCase(depart)) {
		res = constructeurListeCase(grille[x - 1][y], res);
	}
	if(y < taille && getCouleurCase(grille[x][y + 1]) == getCouleurCase(depart)) {
		res = constructeurListeCase(grille[x][y + 1], res);
	}
	if(y > 0 && getCouleurCase(grille[x][y - 1]) == getCouleurCase(depart)) {
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

static ListeCase casesVoisines(ListeCase casesComposanteConnexe, Case ***grille, int taille) {
	ListeCase res = initListeCase();
	Case *tmp = NULL;
	int x = 0;
	int y = 0;
	while(!testListeCaseVide(casesComposanteConnexe)) {
		tmp = getValeurListeCase(casesComposanteConnexe);
		x = getXCase(tmp);
		y = getYCase(tmp);

		if(x < taille && !estPresentDansListeCase(grille[x + 1][y], casesComposanteConnexe)) {
			res = constructeurListeCase(grille[x + 1][y], res);
		}
		if(x > 0 && !estPresentDansListeCase(grille[x - 1][y], casesComposanteConnexe)) {
			res = constructeurListeCase(grille[x - 1][y], res);
		}
		if(y < taille && !estPresentDansListeCase(grille[x][y + 1], casesComposanteConnexe)) {
			res = constructeurListeCase(grille[x][y + 1], res);
		}
		if(y > 0 && !estPresentDansListeCase(grille[x][y - 1], casesComposanteConnexe)) {
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

ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, Case ***grille, int taille, TabComposanteConnexe tabCC) {
	ListeComposanteConnexe composantesVoisines = initListeComposanteConnexe();
	ListeCase casesVoisinesCC = initListeCase();
	ComposanteConnexe *cc = NULL;

	casesVoisinesCC = casesVoisines(casesComposanteConnexe, grille, taille);

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

TabComposanteConnexe listeComposanteConnexeGrille(Case ***grille, int tailleGrille) {
	TabComposanteConnexe res = NULL;
	ComposanteConnexe cc = initComposanteConnexe();
	int **tabTest = tableauTestAppartenance(tailleGrille);
	int i = 0;
	int j = 0;

	for(i = 0; i < tailleGrille; i ++) {
		for(j = 0; j < tailleGrille; j ++) {
			if(tabTest[i][j] == 0) {
				cc = constructeurComposanteConnexe(grille[i][j], grille, tailleGrille);
				res = constructeurTabComposanteConnexe(cc, res);
				tabTest = completeGrilleTest(cc.cases, tabTest);
			}
		}
	}

	return res;
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

