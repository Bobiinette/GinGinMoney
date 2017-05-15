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

static unsigned long long nombreAppelsRecursifs = 0; /**< Compteur du nombre d'appels récursifs de la fonction, à titre informatif*/

/*======================================================= CODE ==========================================================*/

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

int getValeurListeInt(ListeInt l) {
	return l->valeur;
}

ListeInt getSuivantListeInt(ListeInt l) {
	return l->suivant;
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
				/*fclose(*f);
				*f = fopen("./solutionTableau.txt", "w+");
				/*printf("Nouvelle solution en %d coups\n", nbrCoups);*/
				/*fputs(str, *f);
				fputc('\n', *f);*/
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

	printf("\n\n");
	solveurEtape(tabVoisins, ccInitiale, appartenance, taille, tailleMax, &f, str, 0);

	res = *tailleMax;
	/*printf("Nombre appels %llu\n", nombreAppelsRecursifs);*/
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