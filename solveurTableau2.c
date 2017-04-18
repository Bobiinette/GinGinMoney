#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ListeComposanteConnexe.h"
#include "Grille.h"
#include "solveurTableau2.h"

/**\file solveurTableau2.c
 *\brief Solveur à base de tableaux d'entiers
 *	Solution proposée pour le solveur, à base de tableaux de listes d'entiers.
 *	On attribue ici un numéro à chaque composante connexe, et on voit une composante connexe comme un tableau avec 1 colonne et 6 lignes, chaque ligne représantant une couleur de la composante connexe.
 *	Dans chaque ligne, on a une liste de voisins correspondant aux voisins de la composante connexe, avec la couleur correspondant à la ligne sélectionnée.
 */

/*======================================================= HEADERS =======================================================*/

/**\fn static ListeInt initListeInt(void)
 *\brief Initialise un ListeInt à NULL.
 *\param void
 *\return NULL
 */
static ListeInt initListeInt();

/**\fn static ListeInt constructeurListeInt(int v, ListeInt l)
 *\brief Alloue la mmoire pour un nouvel ellement et ajoute un élément en tête de la liste.
 *\param v L'entier à ajouter.
 *\param l La liste à laquelle on rajoute l'entier.
 *\return La liste avec l'élément v rajouté en tête.
 */
static ListeInt constructeurListeInt(int v, ListeInt l);

/**\fn static void destructeurCelluleListeInt(CelluleListeInt *c)
 *\brief Libère la mémoire allouée à un élément d'un ListeInt.
 *\param c Un pointeur vers l'élément de la liste à libérer.
 *\return void
 */
static void destructeurCelluleListeInt(CelluleListeInt *c);

/**\fn static void destructeurListeInt(ListeInt l)
 *\brief Libère la mémoire allouée à un ListeInt, en faisant appel à destructeurCelluleListeInt.
 *\param l Le ListeInt dont on veut libérer la mémoire.
 *\return void
 */
static void destructeurListeInt(ListeInt l);

/**\fn static int estPresentDansListeInt(int v, ListeInt l)
 *\brief Permet de savoir si un élément est présent dans un ListeInt ou non.
 *\param v L'entier dont on veut savoir la présence ou non.
 *\param l Le ListeInt dans lequel on fait la recherche. 
 *\return 1 si l'élément est présent dans la liste, 0 sinon.
 */
static int estPresentDansListeInt(int v, ListeInt l);

/**\fn static ListeInt concatenationListeInt(ListeInt l1, ListeInt l2)
 *\brief Permet la concaténation de 2 ListeInt. On rajoute les éléments de l2 à l1, donc l1 est modifiée.
 *\param l1 La première liste à concaténer. La liste l1 est modifiée.
 *\param l2 La deuxièmre liste à concaténer. l2 n'estas modifiée.
 *\return La liste l1 avec les éléments de l2 rajoutés.
 */
static ListeInt concatenationListeInt(ListeInt l1, ListeInt l2);

/**\fn static ListeInt concatenationListeIntTestAppartenance(ListeInt l1, ListeInt l2, int *appartenance)
 *\brief Permet la concaténation de 2 ListeInt, avec prise en compte de l'aggrandissement de la composante connexe principale. On rajoute les éléments de l2 à l1, donc l1 est modifiée.
 *	Le tableau d'appartenance est un tableau avec n colonnes, n étant le nombre de composantes connexes, qui vaut 1 si la composante connexe appartient à la composante connexe principale, 0 sinon.
 *\param l1 La première liste à concaténer. La liste l1 est modifiée.
 *\param l2 La deuxièmre liste à concaténer. l2 n'estas modifiée.
 *\param appartenance Le tableau d'appartenance, qui permet de déterminer si une composante cnnexe appartient à la composante connexe principale.
 *\return La liste l1 avec les éléments de l2 rajoutés, sans les éléments de l2 qui ont étés absorbés par la composante connexe principale.
 */
static ListeInt concatenationListeIntTestAppartenance(ListeInt l1, ListeInt l2, int *appartenance);

/**\fn static int longueurListeInt(ListeInt l)
 *\brief Permet d'obtenir la taille d'un ListeInt.
 *\param l La liste dont on veut la taille.
 *\return La taille de l, 0 si l vaut NULL.
 */
static int longueurListeInt(ListeInt l);

/**\fn static ListeInt **creeTabVoisins(TabComposanteConnexe tabCC, int taille)
 *\brief Permet de transformer un TabComposanteConnexe en un tableau de taille colonnes et 6 lignes de ListeInt, pour l'utiliser dans le solveur.
 * 	Les 6 lignes correspondant aux 6 couleurs.
 *\param tabCC La liste des composantes connexes générées à partir de la grille.
 *\param taille La taille du TabComposanteConnexe et le nombre de colonnes du ListeInt, à savoir le nombre de composantes connexes de la grille.
 *\return Le ListeInt correspondant au TabComposanteConnexe.
 */
static ListeInt **creeTabVoisins(TabComposanteConnexe tabCC, int taille);

/**\fn static void detruitTabVoisins(ListeInt **tab, int taille)
 *\brief Libère la mémoire allouée à un tableau de taille colonnes et 6 lignes.
 *\param tab Le tableau dont on veut libérer la mémoire.
 *\param taille Le nombre de colones du tableau dont on veut libérer la mémoire.
 *\return void
 */
static void detruitTabVoisins(ListeInt **tab, int taille);

/**\fn static int **miseAjour(int **appartenance, const int taille, int a)
 *\brief Copie les valeurs de la colonne a-1 de appartenance dans la colonne a.
 *\param appartenance Le tableau de ListeInt que l'ont veut mettre à jour.
 *\param taille La taille du tableau de ListeInt.
 *\param a L'étape à mettre à jour.
 *\return Le tableau avec les colones a-1 et a identiques.
 */
static int **miseAjour(int **appartenance, const int taille, int a);

/**\fn static ListeInt **miseAjourCC(ListeInt **ccInitiale, const int taille, int a)
 *\brief Copie les valeurs de la colonne a-1 de ccInitiale dans la colonne a.
 *\param ccInitiale Le tableau de ListeInt que l'ont veut mettre à jour.
 *\param taille La taille du tableau de ListeInt.
 *\param a L'étape à mettre à jour.
 *\return Le tableau avec les colones a-1 et a identiques.
 */
static ListeInt **miseAjourCC(ListeInt **ccInitiale, const int taille, int a);

/**\fn static int nombreVoisinsNonNull(ListeInt *ccPrincipale)
 *\brief Compte le nombre de voisins non nuls d'une composante connexe.
 *\param ccInitiale Le tableau à une dimmension de ListeInt dont on veut le nombre de voisins non nuls.
 *\return Le nombre de voisins non nuls de la composante connexe passée en argument.
 */
static int nombreVoisinsNonNull(ListeInt *ccPrincipale);

/**\fn static ListeInt **changementCouleurSolveur(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **deplacement, const int taille, int couleur, int nombreCoups)
 *\brief Effectue les opérations nécessaires qu changement de couleur. Modifie la colone nombreCoups de ccPrincipale en lui affectant les nouveaux voisins qu'elle obtient avec le changement de couleur.
 *\param tabVoisins Le tableau des voisins. Il n'est pas modifié par la fonction.
 *\param ccPrincipale Le tableau qui correspond à la composanteConnexe principale à plusieurs étapes. L'étape nombreCoups est modifiée par la fonction.
 *\param appartenance La tableau qui répertorie les composantes connexes qui appartiennent à la composante connexe principale. On modifie le tableau en ajoutant les nouvelle composantes connexes qui sont absorbées.
 *\param taille Le nombre de composantes connexes en tout, le nombre de colonnes des différents tableaux.
 *\param couleur La couleur choisie pour le changement de couleur.
 *\param nombreCoups L'étape actuelle. Sert pour se placer dans les taleaux.
 *\return Le tableau de composantes connexes modifié.
 */
static ListeInt **changementCouleurSolveur(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **appartenance, const int taille, int couleur, int nombreCoups);

/**\fn static void solveurEtape(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **appartenance, const int taille, int *tailleMax, FILE **f, char *str, int nbrCoups)
 *\brief Effectue une étape du solveur. Fait un changement de couleur, ou met à jour la solution si on trouve une meilleure solution.
 *\param tabVoisins Le tableau des voisins. Il n'est pas modifié par la fonction.
 *\param ccPrincipale Le tableau qui correspond à la composanteConnexe principale à plusieurs étapes. L'étape nbrCoups est modifiée par la fonction.
 *\param appartenance La tableau qui répertorie les composantes connexes qui appartiennent à la composante connexe principale.
 *\param taille Le nombre de composantes connexes en tout, le nombre de colonnes des différents tableaux.
 *\param tailleMax Un pointeur vers la meilleure solution trouvée.
 *\param str Le tableau de char contenant la solution étudiée à l'étape actuelle.
 *\param nbrCoups Le nombre de coups de la solution actuelle.
 *\return Le tableau de composantes connexes modifié.
 */
static void solveurEtape(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **appartenance, const int taille, int *tailleMax, FILE **f, char *str, int nbrCoups);

static unsigned long long nombreAppelsRecursifs = 0; /**< Compteur du nombre d'appels récursifs de la fonction, à titre informatif*/

/*======================================================= CODE =======================================================*/

struct t_CelluleListeInt {
	int valeur; /**< Valeur de la cellule actuelle de la liste*/
	struct t_CelluleListeInt *suivant; /**< Valeur du voisin de la liste*/
};

void afficheListeInt(ListeInt l) {
	ListeInt tmp = l;
	while(tmp != NULL) {
		printf("%d->", tmp->valeur);
		tmp = tmp->suivant;
	}
	printf("\n");
}

void afficheTabVoisins(ListeInt **tab, int taille) {
	int i = 0; int j = 0;
	for(i = 0; i < taille; i++) {
		for(j = 0; j < 6; j ++) {
			if(tab[i][j] == NULL) {
				printf("%d | %d : null\n", i, j);
			}
			else {
				printf("%d | %d : ", i, j);
				afficheListeInt(tab[i][j]);
			}
		}
		printf(" \n");
	}
	printf("---\n");
}

ListeInt initListeInt() {
	return NULL;
}

ListeInt constructeurListeInt(int v, ListeInt l) {
	if(v == -1) {
		return l;
	}
	CelluleListeInt *c = (CelluleListeInt *)calloc(1, sizeof(CelluleListeInt));
	c->valeur = v;
	c->suivant = l;
	return c;
}

void destructeurCelluleListeInt(CelluleListeInt *c) {
	free(c);
	c = NULL;
}

void destructeurListeInt(ListeInt l) {
	ListeInt tmp = l;
	while(l != NULL) {
		tmp = l->suivant;
		destructeurCelluleListeInt(l);
		l = tmp;
	}
	l = NULL;
}

int estPresentDansListeInt(int v, ListeInt l) {
	ListeInt tmp = l;
	while(l != NULL) {
		if(l->valeur == v) {
			return 1;
		}
		l = l->suivant;
	}
	l = tmp;
	return 0;
}

/*La liste l1 est modifiée*/
ListeInt concatenationListeInt(ListeInt l1, ListeInt l2) {
	ListeInt res = l1;
	res = initListeInt();
	ListeInt tmp2 = l2;
	while(tmp2 != NULL) {
		if(!estPresentDansListeInt(tmp2->valeur, res) && tmp2->valeur >= 0) {
			res = constructeurListeInt(tmp2->valeur, res);
		}
		tmp2 = tmp2->suivant;
	}
	return res;
}

ListeInt concatenationListeIntTestAppartenance(ListeInt l1, ListeInt l2, int *appartenance) {
	ListeInt res = l1;
	ListeInt tmp2 = l2;
	int val = 0;
	while(tmp2 != NULL) {
		if(!estPresentDansListeInt(tmp2->valeur, res) && appartenance[tmp2->valeur] == 0) {
			res = constructeurListeInt(tmp2->valeur, res);
		}
		tmp2 = tmp2->suivant;
	}
	return res;
}

int longueurListeInt(ListeInt l) {
	ListeInt tmp = l;
	int res = 0;
	while(tmp != NULL) {
		if(tmp->valeur >= 0) {
			res ++;
		}
		tmp = tmp->suivant;
	}
	return res;
}

ListeInt **creeTabVoisins(TabComposanteConnexe tabCC, int taille) {
	/*Des tableaux de n colones, 6 lignes*/
	ListeComposanteConnexe lcc;
	ListeInt **res = NULL;
	ComposanteConnexe *cc = NULL;
	TabComposanteConnexe tmp = tabCC;
	int couleur = 0;
	int i = 0;
	int j = 0;

	res = (ListeInt**)calloc(taille, sizeof(ListeInt*));
	for(i = 0; i < taille; i++) {
		res[i] = (ListeInt*)calloc(6, sizeof(ListeInt));
		for(j = 0; j < 6; j++) {
			res[i][j] = NULL;
		}
	}

	i = 0;

	while(!estVideTabComposanteConnexe(tmp)) {
		lcc = getComposantesVoisinesComposanteConnexe(getValeurTabComposanteConnexe(tmp));
		while(!estVideListeComposanteConnexe(lcc)) {
			cc = getValeurListeComposanteConnexe(lcc);
			couleur = getCouleurComposanteConnexe(cc) - 1;
			res[i][couleur] = constructeurListeInt(rangTabComposanteConnexe(cc, tabCC), res[i][couleur]);
			lcc = getSuivantListeComposanteConnexe(lcc);
		}
		i ++;
		tmp = getSuivantTabComposanteConnexe(tmp);
	}

	return res;
}

void detruitTabVoisins(ListeInt **tab, int taille) {
	int i = 0;
	int j = 0;

	for(i = 0; i < taille; i++) {
		for(j = 0; j < 6; j++) {
			destructeurListeInt(tab[i][j]);
		}
		free(tab[i]);
	}
	free(tab);
}

int **miseAjour(int **appartenance, const int taille, int a) {
	int i = 0;
	for(i = 0; i < taille; i++) {
		appartenance[a][i] = appartenance[a - 1][i];
	}
	return appartenance;
}

ListeInt **miseAjourCC(ListeInt **ccInitiale, const int taille, int a) {
	int i = 0;
	for(i = 0; i < 6; i++) {
		destructeurListeInt(ccInitiale[a][i]);
		ccInitiale[a][i] = concatenationListeInt(NULL, ccInitiale[a - 1][i]);
	}
	return ccInitiale;
}

ListeInt **changementCouleurSolveur(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **appartenance, const int taille, int couleur, int nombreCoups) {
	ListeInt ccBonneCouleur = ccPrincipale[nombreCoups][couleur];
	ListeInt save = ccBonneCouleur;
	ccPrincipale[nombreCoups][couleur] = NULL;
	int i = 0;
	int val = 0;
	for(i = 0; i < 6; i++) {
		if(i != couleur) {
			ccPrincipale[nombreCoups][i] = concatenationListeIntTestAppartenance(ccPrincipale[nombreCoups][i], ccPrincipale[nombreCoups - 1][i], appartenance[nombreCoups]);
		}
	}
	while(ccBonneCouleur != NULL) {
		val = ccBonneCouleur->valeur;
		appartenance[nombreCoups][val] = 1;
		for(i = 0; i < 6; i++) {
			if(i != couleur) {
				ccPrincipale[nombreCoups][i] = concatenationListeIntTestAppartenance(ccPrincipale[nombreCoups][i], tabVoisins[val][i], appartenance[nombreCoups]);
			}
		}
		ccBonneCouleur = ccBonneCouleur->suivant;
	}
	destructeurListeInt(save);
	return ccPrincipale;
}

int nombreVoisinsNonNull(ListeInt *ccPrincipale) {
	int i = 0;
	int res = 0;
	for(i = 0; i < 6; i ++) {
		if(ccPrincipale[i] != NULL) {
			res +=1;
		}
	}
	return res;
}

int tabVoisinsPlein(int *appartenance, int taille) {
	int i;
	for(i = 0; i < taille; i ++) {
		if(appartenance[i] < taille) {
			return 0;
		}
	}
	return 1;
}

void solveurEtape(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **appartenance, const int taille, int *tailleMax, FILE **f, char *str, int nbrCoups) {
	/*On veut UNE solution en un nombre minimum de coups*/
	appartenance = miseAjour(appartenance, taille, nbrCoups + 1);
	ccPrincipale = miseAjourCC(ccPrincipale, taille, nbrCoups + 1);
	int i = 0;
	int j = 0;
	nombreAppelsRecursifs += 1;
	int *nouveauDeplacement = NULL;
	int nombreNonNull = 0;

	if(tabVoisins == NULL) {
		fprintf(stderr, "Tab voisins vide\n");
	}
	else {
		nombreNonNull = nombreVoisinsNonNull(ccPrincipale[nbrCoups]);
		if(nombreNonNull == 0) {
			/*printf("Solution trouvée\n");*/
			if(nbrCoups < *tailleMax) {
				*tailleMax = nbrCoups;
				fclose(*f);
				*f = fopen("./solution.txt", "w+");
				printf("Nouvelle solution en %d coups\n", nbrCoups);
				fputs(str, *f);
				fputc('\n', *f);
			}
			return;
		}
		/*Un peu d'optimisation ici, si il reste plus de couleurs que de coups restants*/
		else if(nombreNonNull + nbrCoups >= *tailleMax) {
			return;
		}
		for(i = 0; i < 6; i ++) {
			if(ccPrincipale[nbrCoups][i] != NULL) {
				if (nbrCoups < *tailleMax) {
					ccPrincipale = changementCouleurSolveur(tabVoisins, ccPrincipale, appartenance, taille, i, nbrCoups + 1);

					str[nbrCoups] = conversionEntierChar(i + 1);
					str[nbrCoups + 1] = '\0';
					/*printf("Salut : %s nbrCoups : %d, nombre d'appels récursifs %llu et i : %d\n", str, nbrCoups + 1, nombreAppelsRecursifs, i);
					*//*for(j = 0; j < 6; j ++) {
						afficheListeInt(ccPrincipale[nbrCoups][j]);
					}
					printf("---\n");*/
					solveurEtape(tabVoisins, ccPrincipale, appartenance, taille, tailleMax, f, str, nbrCoups + 1);
					appartenance = miseAjour(appartenance, taille, nbrCoups + 1);
					ccPrincipale = miseAjourCC(ccPrincipale, taille, nbrCoups + 1);
				}
			}
		}
	}
	return;
}

int solveurTableau2(TabComposanteConnexe tabCC, ComposanteConnexe *cc) {
	const int taille = longueurTabComposanteConnexe(tabCC);
	char str[taille + 1];
	int i = 0;
	int j = 0;
	str[0] = '\0';
	ListeInt **tabVoisins = creeTabVoisins(tabCC, taille);
	/*afficheTabVoisins(tabVoisins, taille);*/
	int *tailleMax;
	int res = 0;
	ListeInt **ccInitiale = (ListeInt **)calloc(taille + 1, sizeof(ListeInt*));
	for(i = 0; i < taille + 1; i ++) {
		ccInitiale[i] = (ListeInt *)calloc(6, sizeof(ListeInt));
	}
	FILE *f = fopen("./solutionTableau.txt", "w+");
	tailleMax = calloc(1, sizeof(int));
	int **appartenance = calloc(taille + 1, sizeof(int *));
	for(i = 0; i < taille + 1; i ++) {
		appartenance[i] = calloc(taille, sizeof(int));
	}
	appartenance[0][taille - 1] = 1;
	*tailleMax = taille;

	for(i = 0; i < 6; i ++) {
		ccInitiale[0][i] = concatenationListeInt(ccInitiale[0][i], tabVoisins[taille - 1][i]);
	}


	solveurEtape(tabVoisins, ccInitiale, appartenance, taille, tailleMax, &f, str, 0);

	res = *tailleMax;
	if(fgets(str, taille, f) != NULL) {
		printf("Solution : %s\n", str);
	}
	printf("Nombre appels %llu\n", nombreAppelsRecursifs);
	for(i = 0; i < taille + 1; i ++) {
		free(appartenance[i]);
	}
	free(appartenance);
	for(i = 0; i < taille + 1; i ++) {
		for(j = 0; j < 6; j ++) {
			destructeurListeInt(ccInitiale[i][j]);
		}
		free(ccInitiale[i]);
	}
	free(ccInitiale);
	fclose(f);
	detruitTabVoisins(tabVoisins, taille);
	free(tailleMax);
	return res;
}