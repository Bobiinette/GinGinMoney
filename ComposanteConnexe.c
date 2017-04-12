#include <stdlib.h>
#include <stdio.h>

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

static ComposanteConnexe initComposanteConnexe() {
	ComposanteConnexe res;
	res.couleur = H;
	res.listeVoisins = initListeComposanteConnexe();
	res.cases = initListeCase();
	return res;
}

/**\fn ComposanteConnexe constructeurComposanteConnexe(Case *emplacementInitial, Case ***grille, int taille)
 *\brief Constructeur d'une composante connexe. Permet de créer une composante connexe à partir d'une case et de la grille. Ne crée pas la liste des voisins de la composante connexe.
 *		Voir aussi voisinsConnexes().
 *\param emplacementInitial Pointeur vers la case à partir de laquelle on veut créer une composante connexe.
 *\param grille Pointeur vers la grille de jeu. La grille doit-être non NULL.
 *\param taille Taille de la grille de jeu.
 *\return ComposanteConnexe initialisée avec ses cases et sa couleur, mais pas ses composantes connexes voisines.
 */

static ComposanteConnexe constructeurComposanteConnexe(Case *emplacementInitial, Case **grille, int taille) {
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

/**\fn ComposanteConnexe creeComposanteConnexe(Case *emplacementInitial, Case ***grille, int taille)
 *\brief Fonction retournant un ponteur vers une composante connexe qu'il crée. Permet de créer une composante connexe à partir d'une case et de la grille. Ne crée pas la liste des voisins de la composante connexe.
 *		Utilie pour les tests unitaires.
 *\param emplacementInitial Pointeur vers la case à partir de laquelle on veut créer une composante connexe.
 *\param grille Pointeur vers la grille de jeu. La grille doit-être non NULL.
 *\param taille Taille de la grille de jeu.
 *\return ComposanteConnexe initialisée avec ses cases et sa couleur, mais pas ses composantes connexes voisines.
 */

ComposanteConnexe * creeComposanteConnexe(Case * emplacementInitial, Case **grille, int taille) {
	ComposanteConnexe *cc = NULL;
	cc = (ComposanteConnexe *)calloc(1, sizeof(ComposanteConnexe));
	*cc = constructeurComposanteConnexe(emplacementInitial, grille, taille);
	return cc;
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
			cc->listeVoisins = NULL;
		}
		if(!testListeCaseVide(cc->cases)) {
			destructeurListeCase(cc->cases);
			cc->cases = NULL;
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

void setCouleurComposanteConnexe(ComposanteConnexe *cc, Couleur c){
	cc->couleur = c;
}

void setComposantesVoisinesComposanteConnexe(ComposanteConnexe *cc, ListeComposanteConnexe l){
	cc->listeVoisins = l;
}

void setCasesComposanteConnexe(ComposanteConnexe *cc,ListeCase lc){
	cc->cases = lc;
}

/**\fn ListeCase voisinsConnexes(Case *depart, Case ***grille, int taille)
 *\brief Fonction pour obtenir la liste de toutes les cases voisines de même couleur d'une case passée en paramètre.
 *\param depart Pointeur vers la case dont ont veut toutes les cases voisines de même couleur.
 *\param grille Pointeur vers la grille de jeu, non NULL.
 *\param taille La taille de la grille de jeu.
 *\return La liste des cases voisines de la case depart de même couleur.
 */

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

/**\fn static int **tableauTestAppartenance(int taille)
 *\brief Fonction qui renvoie un tableau d'entier remplis de 0.
 *\param taille La taille du tableau.
 *\return Un pointeur vers le tableau 2D crée.
 */

static int **tableauTestAppartenance(int taille) {
	int i = 0;
	int **res = NULL;
	res = calloc(taille, sizeof(int*));

	for(i = 0; i < taille; i ++) {
		res[i] = calloc(taille, sizeof(int));
	}
	return res;
}

/**\fn static int **completeGrilleTest(ListeCase aCompleter, int **grilleTest)
 *\brief Fonction qui permet de mettre à jour les cases complétées dans un tableau 2D de test.
 *\param aCompleter La liste des cases que l'on a déjà complétées.
 *\param grilleTest Le tableau 2D de test que l'on veut compléter.
 *\return Le tableau de test complété.
 */

static int **completeGrilleTest(ListeCase aCompleter, int **grilleTest) {
	while(!testListeCaseVide(aCompleter)) {
		grilleTest[getXCase(getValeurListeCase(aCompleter))][getYCase(getValeurListeCase(aCompleter))] = 1;
		aCompleter = getSuivantListeCase(aCompleter);
	}
	return grilleTest;
}

/**\fn static void destructeurTableauTest(int **tab, int taille)
 *\brief Destructeur du tableau 2D test, libère la mémoire allouée.
 *\param tab Tableau 2D d'entier à détruire.
 *\param taille La taille du tableau 2D à détruire.
 *\return void
 */

static void destructeurTableauTest(int **tab, int taille) {
	int i = 0;
	for(i = 0; i < taille; i++) {
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
}

/**\fn int estIdentique(ComposanteConnexe *cc1, ComposanteConnexe *cc2)
 *\brief Fonction de test pour savoir si 2 ComposantesConnexes sont identiques.
 *\param cc1 La première composante connexe à comparer.
 *\param cc2 La deuxième composante connexe à comparer.
 *\return Renvoie 0 si les composantes connexes sont différentes, 1 sinon.
 */

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

/**\fn static ListeCase casesVoisines(ListeCase casesComposanteConnexe, Case ***grille, int taille)
 *\brief Une fonction qui renvoie toutes les cases voisines d'une liste de cases donnée en argument.
 *\param casesComposanteConnexe La liste des cases dont on veut les voisins.
 *\param grille La grille qui contient toutes les cases du jeu.
 *\param taille La taille de la grille.
 *\return La liste des cases voisines à la liste de cases passées en paramètre.
 */

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

/**\fn static void supprimeCasesDansListe(ListeCase casesAEnlever, ListeCase *listeATronquer)
 *\brief Suprime une liste de cases dans une autre liste de cases. L'ordre des cases dans les listes ne rentre pas en compte.
 *\param casesAEnlever La liste des cases à enlever.
 *\param listeATronquer La liste des cases à laquelle on enlève les cases.
 *\return void
 */

static ListeCase supprimeCasesDansListe(ListeCase casesAEnlever, ListeCase listeATronquer) {
	int s = 0;
	while(!testListeCaseVide(casesAEnlever) && !testListeCaseVide(listeATronquer)) {
		listeATronquer = supprimeElementListeCase(getValeurListeCase(casesAEnlever), listeATronquer);
		casesAEnlever = getSuivantListeCase(casesAEnlever);
		s ++;
	}
	return listeATronquer;
}

/**\fn ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, Case ***grille, int taille, TabComposanteConnexe tabCC)
 *\brief Fonction qui définie les composantes connexes voisines d'une liste de cases donnée en paramètre.
 *\param casesComposanteConnexe La liste des cases de la composante connexe dont on veut les voisins.
 *\param grille La grille de jeu contenant toutes les cases.
 *\param taille La taille de la grille.
 *\param TabComposanteConnexe La liste de toutes les composantes connexes de la grille.
 *\return La liste de toutes les composantes connexes voisines à la liste de cases passée en paramètre.
 */

static ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, Case **grille, int taille, TabComposanteConnexe tabCC) {
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

static void changementCouleurCase(ComposanteConnexe *cc, Couleur couleur) {
	ListeCase tmp = cc->cases;
	while(!testListeCaseVide(cc->cases)) {
		setCouleur(getValeurListeCase(cc->cases), couleur);
		cc->cases = getSuivantListeCase(cc->cases);
	}
	cc->cases = tmp;
}

/**\fn ComposanteConnexe *changementCouleur(ComposanteConnexe *ccInitiale, TabComposanteConnexe toutesComposantesConnexes, Couleur nouvelleCouleur)
 *\brief Fonction qui permet le changement de couleur d'une composante connexe. Met à jour les cases et les composantes connexes voisines de la composante connexe.
 *\param ccInitiale La composante connexe dont on veut changer le couleur.
 *\param touteComposantesConnexes Un pointeur vers la liste de toutes les composantes connexes.
 *\param nouvelleCouleur La nouvelle couleur de ccInitiale
 *\return Renvoie la composante connexe avec la nouvelle couleur et ses cases et composantes connexes voisines mis à jour.
 */

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


/**\struct TabComposanteConnexe ComposanteConnexe.h
 *\brief Structure de liste de composante connexe.
 */
struct t_CelluleTabComposanteConnexe {
	ComposanteConnexe composanteConnexe; /**< ComposanteConnexe de la tête de la liste.*/
	struct t_CelluleTabComposanteConnexe *suivant; /**< Pointeur vers le suivant de la liste*/
};

/**\fn TabComposanteConnexe initTabComposanteConnexe()
 *\brief initialise un TabComposantConnexe à NULL.
 *\param void
 *\return NULL;
 */

TabComposanteConnexe initTabComposanteConnexe() {
	return NULL;
}

/**\fn int estVideTabComposanteConnexe(TabComposanteConnexe tabCC)
 *\brief Permet de savoir si un TabComposanteConnexe est NULL.
 *\param tabCC Le TabComposanteConnexe que l'on veut tester.
 *\return 0 si tabCC n'est pas NULL, 1 sinon.
 */

int estVideTabComposanteConnexe(TabComposanteConnexe tabCC) {
	return (tabCC == NULL);
}

/**\fn TabComposanteConnexe constructeurTabComposanteConnexe(ComposanteConnexe cc, TabComposanteConnexe tabCC)
 *\brief Constructeur d'un TabComposanteConnexe.
 *\param cc La composante connexe que l'on veut ajouter à la liste.
 *\param tabCC Le TabComposanteConnexe auquel on veut ajouter la composante connexe.
 *\return Un pointeur vers le TabComposanteConnexe nouvellement crée.
 */

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


/**\fn ComposanteConnexe * getValeurTabComposanteConnexe(TabComposanteConnexe tabCC)
 *\brief Permet d'obtenir un pointeur vers la tete d'un TabComposanteConnexe.
 *\param tabCC Le TabComposanteConnexe dont on veut la tete.
 *\return Un pointeur vers la tete du TabComposanteConnexe.
 */

ComposanteConnexe * getValeurTabComposanteConnexe(TabComposanteConnexe tabCC) {
	return &(tabCC->composanteConnexe);
}

/**\fn TabComposanteConnexe getSuivantTabComposanteConnexe(TabComposanteConnexe tabCC)
 *\brief Permet d'obtenir la queue du TabComposanteConnexe.
 *\param tabCC Le TabComposanteConnexe dont on veut le suivant.
 *\return La queue de TabComposanteConnexe.
 */

TabComposanteConnexe getSuivantTabComposanteConnexe(TabComposanteConnexe tabCC) {
	return tabCC->suivant;
}


/**\fn void destructeurCelluleTabComposanteConnexe(CelluleTabComposanteConnexe *cell)
 *\brief Destructeur d'une cellule de TabComposanteConnexe, libère la mémoire d'une cellule de TabComposanteConnexe et de la composante connexe qui le constitue.
 *\param cell Pointeur vers la cellule de TabComposanteConnexe que l'on veut libérer.
 *\return void
 */

void destructeurCelluleTabComposanteConnexe(CelluleTabComposanteConnexe *cell) {
	destructeurComposanteConnexe(&(cell->composanteConnexe));
	free(cell);
	cell = NULL;
}

/**\fn void destructeurTabComposanteConnexe(TabComposanteConnexe tabCC)
 *\brief Destructeur de TabComposanteConnexe. Libère la mémoire d'une TabComposanteConnexe et de tous ces composants. Fait appel à destructeurCelluleTabComposanteConnexe.
 *\param tabCC Le TabComposanteConnexe que l'on veut détruire.
 *\return void
 */

void destructeurTabComposanteConnexe(TabComposanteConnexe tabCC) {
	TabComposanteConnexe tmp = initTabComposanteConnexe();
	while(!estVideTabComposanteConnexe(tabCC)) {
		tmp = tabCC;
		tabCC = tabCC->suivant;
		destructeurCelluleTabComposanteConnexe(tmp);
	}
}

/**\fn TabComposanteConnexe listeComposanteConnexeGrille(Case ***grille, int tailleGrille)
 *\brief Fonction qui permet de construire toutes les composantes connexes d'une grille et de les stocker dans un TabComposanteConnexe.
 *\param grille La grille à partir de laquelle on veut créer le TabComposanteConnexe.
 *\param tailleGrille La taille de la grille.
 *\return Le TabComposanteConnexe avec toutes les composantes connexes crées dedans.
 */

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

/**\fn TabComposanteConnexe creeVoisins(TabComposanteConnexe *tabCC, Case **grille, int taille)
 *\brief Crée la liste des voisins de chacune des composantes connes d'un TabComposanteConnexe
 *\param tabCC Le TabComposanteConnexe à qui l'on veut créer les voisins  pour chacune des composantes connexes.
 *\param grille La grille de jeu.
 *\param taille La taille de la grille de jeu.
 */

TabComposanteConnexe creeVoisins(TabComposanteConnexe tabCC, Case **grille, int taille) {
	TabComposanteConnexe save = tabCC;
	while(!estVideTabComposanteConnexe(tabCC)) {
		(tabCC->composanteConnexe).listeVoisins = definieComposantesConnexesVoisines((tabCC->composanteConnexe).cases, grille, taille, save);
		tabCC = tabCC->suivant;
	}
	tabCC = save;
	return tabCC;
}

/**\fn int testVictoire(TabComposanteConnexe tabCC)
 *\brief Fonction qui test savoir si il n'y a plus qu'une seule composante connexe.
 *\param taCC Le TabComposanteConnexe qui contient toutes les composantes connexes.
 *\return 0 si la longueur de la composante connexe est différente de 1, 1 sinon.
 */

int testVictoire(TabComposanteConnexe tabCC, ComposanteConnexe *cc) {
	if(longueurTabComposanteConnexe(tabCC)==1) {
		return 1;
	}
	if(longueurListeComposanteConnexe(cc->listeVoisins) == 0) {
		return 1;
	}
	return 0;
}

/**\fn int longueurTabComposanteConnexe(TabComposanteConnexe tabCC)
 *\brief Fonction pour calculer la longueur d'un TabComposanteConnexe.
 *\param tabCC Le TabComposanteConnexe dont on veut la longueur.
 *\return La longueur du TabComposanteConnexe.
 */

int longueurTabComposanteConnexe(TabComposanteConnexe tabCC) {
	int longeur = 0;
	while (!estVideTabComposanteConnexe(tabCC)){
	  longeur = longeur + 1;
	  tabCC = tabCC->suivant;
	}
	return longeur;
}

/**\fn void supprimeElementTabComposanteConnexe(TabComposanteConnexe *tabCC, ComposanteConnexe element)
 *\brief Supprime l'élément spécifié du TabComposanteConnexe.
 *\param tabCC Un pointeur vers un TabComposanteConnexe auquel on veut supprimer un élément.
 *\param element L'élément que l'on veut supprimer dans le TabComposanteConnexe.
 *\return void
 */

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
            if(tabCC->suivant == NULL) {
            	tabCC->suivant = NULL;
            }
            else {
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

/**\fn static int estDansComposanteConnexe(Case *c, ComposanteConnexe cc)
 *\brief Permet de savoir si une case est dans la composante connexe.
 *\param c La case à tester.
 *\param cc La composante connexe dont on veut savoir si elle contient la case.
 *\return 0 si la cases n'est pas dedans, 1 sinon.
 */

static int estDansComposanteConnexe(Case *c, ComposanteConnexe cc) {
	return estPresentDansListeCase(c, cc.cases);
}

/**\fn ComposanteConnexe *rechercheElementTabComposanteConnexeAvecCase(Case *c, TabComposanteConnexe tabCC)
 *\brief Permet de rechercher une composante connexe dans un TabComposanteConnexe à partir d'une case qui la compose.
 *\param c La case dont on veut la composante connexe à laquelle elle appartient.
 *\param tabCC Le TabComposanteConnexe dans lequel on cherche la composante connexe.
 *\return Un pointeur vers la composante connexe dans le TabComposanteConnexe qui contient la case que l'on cherche.
 */

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

/**\fn ComposanteConnexe *rechercheElementTabComposanteConnexe(ComposanteConnexe *cc, TabComposanteConnexe tabCC)
 *\brief Recherche une composante connexe dans un TabComposanteConnexe.
 *\param cc La composante connexe que l'on cherche.
 *\param tabCC Le TabComposanteConnexe dans lequel on cherche la composante connexe.
 *\return Un pointeur vers la composante connexe que l'on cherche dans le TabComposanteConnexe.
 */

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
