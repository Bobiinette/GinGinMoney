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

/**\fn static ListeCase casesVoisines(ListeCase casesComposanteConnexe, Case ***grille, int taille)
 *\brief Une fonction qui renvoie toutes les cases voisines d'une liste de cases donnée en argument.
 *\param casesComposanteConnexe La liste des cases dont on veut les voisins.
 *\param grille La grille qui contient toutes les cases du jeu.
 *\param taille La taille de la grille.
 *\return La liste des cases voisines à la liste de cases passées en paramètre.
 */

static ListeCase casesVoisines(ListeCase casesComposanteConnexe, Case **grille, int taille) {
	ListeCase res = initListeCase();
	Case *tmp = NULL;
	int x = 0;
	int y = 0;
	while(!testListeCaseVide(casesComposanteConnexe)) {
		tmp = getValeurListeCase(casesComposanteConnexe);
		x = getXCase(tmp);
		y = getYCase(tmp);

		if(x < taille - 1&& !estPresentDansListeCase(getCaseGrille(grille, x + 1, y), casesComposanteConnexe)) {
			res = constructeurListeCase(getCaseGrille(grille, x + 1, y), res);
		}
		if(x > 0 && !estPresentDansListeCase(getCaseGrille(grille, x - 1, y), casesComposanteConnexe)) {
			res = constructeurListeCase(getCaseGrille(grille, x - 1, y), res);
		}
		if(y < taille - 1 && !estPresentDansListeCase(getCaseGrille(grille, x, y + 1), casesComposanteConnexe)) {
			res = constructeurListeCase(getCaseGrille(grille, x, y + 1), res);
		}
		if(y > 0 && !estPresentDansListeCase(getCaseGrille(grille, x, y - 1), casesComposanteConnexe)) {
			res = constructeurListeCase(getCaseGrille(grille, x, y - 1), res);
		}

		casesComposanteConnexe = getSuivantListeCase(casesComposanteConnexe);
	}
	return res;
}

/**\fn static void supprimeCasesDansListe(ListeCase casesAEnlever, ListeCase *listeATronquer)
 *\brief Suprime une liste de cases dans une autre liste de cases. L'ordre des cases dans les listes ne rentre pas en compte.
 *\param casesAEnlever La liste des cases à enlever.
 *\param listeATronquer Un pointeur vers la liste des cases à laquelle on enlève les cases.
 *\return void
 */

static void supprimeCasesDansListe(ListeCase casesAEnlever, ListeCase *listeATronquer) {
	while(!testListeCaseVide(casesAEnlever)) {
		supprimeElementListeCase(getValeurListeCase(casesAEnlever), listeATronquer);
		casesAEnlever = getSuivantListeCase(casesAEnlever);
	}
}

/**\fn ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, Case ***grille, int taille, TabComposanteConnexe tabCC)
 *\brief Fonction qui définie les composantes connexes voisines d'une liste de cases donnée en paramètre.
 *\param casesComposanteConnexe La liste des cases de la composante connexe dont on veut les voisins.
 *\param grille La grille de jeu contenant toutes les cases.
 *\param taille La taille de la grille.
 *\param TabComposanteConnexe La liste de toutes les composantes connexes de la grille.
 *\return La liste de toutes les composantes connexes voisines à la liste de cases passée en paramètre.
 */

ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, Case **grille, int taille, TabComposanteConnexe tabCC) {
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

/**\fn ComposanteConnexe *changementCouleur(ComposanteConnexe *ccInitiale, TabComposanteConnexe *toutesComposantesConnexes, Couleur nouvelleCouleur)
 *\brief Fonction qui permet le changement de couleur d'une composante connexe. Met à jour les cases et les composantes connexes voisines de la composante connexe.
 *\param ccInitiale La composante connexe dont on veut changer le couleur.
 *\param touteComposantesConnexes Un pointeur vers la liste de toutes les composantes connexes.
 *\param nouvelleCouleur La nouvelle couleur de ccInitiale
 *\return Renvoie la composante connexe avec la nouvelle couleur et ses cases et composantes connexes voisines mis à jour.
 */

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

/**\fn void destructeurCelluleTabComposanteConnexe(CelluleTabComposanteConnexe *cell)
 *\brief Destructeur d'une cellule de TabComposanteConnexe, libère la mémoire d'une cellule de TabComposanteConnexe et de la composante connexe qui le constitue.
 *\param cell Pointeur vers la cellule de TabComposanteConnexe que l'on veut libérer.
 *\return void
 */

void destructeurCelluleTabComposanteConnexe(CelluleTabComposanteConnexe *cell) {
	destructeurComposanteConnexe(&(cell->composanteConnexe));
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

/**\fn int testVictoire(TabComposanteConnexe tabCC)
 *\brief Fonction qui test savoir si il n'y a plus qu'une seule composante connexe.
 *\param taCC Le TabComposanteConnexe qui contient toutes les composantes connexes.
 *\return 0 si la longueur de la composante connexe est différente de 1, 1 sinon.
 */

int testVictoire(TabComposanteConnexe tabCC) {
	return (longueurTabComposanteConnexe(tabCC)==1);
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

void supprimeElementTabComposanteConnexe(TabComposanteConnexe *tabCC, ComposanteConnexe element) {
    TabComposanteConnexe tmp = initTabComposanteConnexe();
    TabComposanteConnexe save = initTabComposanteConnexe();
    save = *tabCC;

    if(estIdentique(&((*tabCC)->composanteConnexe), &element)) {
        *tabCC = (*tabCC)->suivant;
        CelluleTabComposanteConnexe(save);
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
	}
	return cc;
}

/**\fn ComposanteConnexe *rechercheElementTabComposanteConnexe(ComposanteConnexe *cc, TabComposanteConnexe tabCC)
 *\brief Recherche une composante connexe dans un TabComposanteConnexe.
 *\param cc La composante connexe que l'on cherche.
 *\param tabCC Le TabComposanteConnexe dans lequel on cherche la composante connexe.
 *\return Un pointeur vers la composante connexe que l'on cherche dans le TabComposanteConnexe.
 */

ComposanteConnexe *rechercheElementTabComposanteConnexe(ComposanteConnexe *cc, TabComposanteConnexe tabCC) {
	while(!estVideTabComposanteConnexe(tabCC)) {
		if(estIdentique(cc, &(tabCC->composanteConnexe))) {
			return &(tabCC->composanteConnexe);
		}
	}
	return NULL;
}

