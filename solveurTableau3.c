#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ListeComposanteConnexe.h"
#include "Grille.h"
#include "solveurTableau2.h"

unsigned long long nombreAppelsRecursifs = 0;
ListeVerif listeTest = NULL;

struct t_CelluleListeInt {
	int valeur;
	struct t_CelluleListeInt *suivant;
};

struct t_CelluleListeVerif {
	unsigned char *valeur;
	int taille;
	struct t_CelluleListeVerif *suivant;
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
	ListeInt res = NULL;
	res = initListeInt();
	ListeInt tmp1 = l1;
	ListeInt tmp2 = l2;
	while(tmp1 != NULL) {
		if(tmp1->valeur >= 0) {
			res = constructeurListeInt(tmp1->valeur, res);
		}
		tmp1 = tmp1->suivant;
	}
	while(tmp2 != NULL) {
		if(!estPresentDansListeInt(tmp2->valeur, res) && tmp2->valeur >= 0) {
			res = constructeurListeInt(tmp2->valeur, res);
		}
		tmp2 = tmp2->suivant;
	}
	destructeurListeInt(l1);
	return res;
}

ListeInt concatenationListeIntDecalage(ListeInt l1, ListeInt l2, int *decalage) {
	ListeInt res = NULL;
	ListeInt tmp1 = l1;
	ListeInt tmp2 = l2;
	int val = 0;
	while(tmp1 != NULL) {
		val = tmp1->valeur - decalage[tmp1->valeur];
		if(val >= 0) {
			res = constructeurListeInt(tmp1->valeur, res);
		}
		tmp1 = tmp1->suivant;
	}
	while(tmp2 != NULL) {
		val = tmp2->valeur - decalage[tmp2->valeur];
		if(!estPresentDansListeInt(tmp2->valeur, res) && val >= 0) {
			res = constructeurListeInt(tmp2->valeur, res);
		}
		tmp2 = tmp2->suivant;
	}
	destructeurListeInt(l1);
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

ListeVerif constructeurListeVerif(int *v, int t, ListeVerif l) {
	int i = 0;
	int j = 0;
	int p = 0;
	if(v == NULL) {
		return l;
	}
	CelluleListeVerif *c = (CelluleListeVerif *)calloc(1, sizeof(CelluleListeVerif));
	c->taille = t/8 + 1;
	c->valeur = calloc(c->taille, sizeof(char));
	for(i = 0; i < c->taille; i++) {
		p = 1;
		for(j = 0; j < 8; j ++) {
			if(8 * i + j < t) {
				if(v[i * 8 + j] >= t) {
					c->valeur[i] += p;
				}
			}
			p *= 2;
		}
	}
	c->suivant = l;
	return c;
}

void destructeurCelluleListeVerif(CelluleListeVerif *c) {
	free(c->valeur);
	free(c);
	c = NULL;
}

void destructeurListeVerif(ListeVerif l) {
	ListeVerif tmp = l;
	while(l != NULL) {
		tmp = l->suivant;
		destructeurCelluleListeVerif(l);
		l = tmp;
	}
	l = NULL;
}

int estEgal(char *c1, char *c2, int taille) {
	int i = 0;
	for(i = 0; i < taille; i ++) {
		if(c1[i] != c2[i]) {
			return 0;
		}
	}
	return 1;
}

int estPresentDansListeVerif(int *v, int taille, ListeVerif l) {
	ListeVerif tmp = l;
	int i = 0;
	int j = 0;
	int p = 0;
	int res = 1;
	const int t = taille / 8 + 1;
	unsigned char vchar[t];

	for(i = 0; i < t; i++) {
		p = 1;
		vchar[i] = 0;
		for(j = 0; j < 8; j ++) {
			if(8 * i + j < taille) {
				if(v[i * 8 + j] >= taille) {
					vchar[i] += p;
				}
			}
			p *= 2;
		}
	}

	while(l != NULL) {
		if(estEgal(l->valeur, vchar, t)) {
			return 1;
		}
		l = l->suivant;
	}
	l = tmp;
	return 0;
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

int **miseAjour(int **deplacement, const int taille, int a) {
	int i = 0;
	for(i = 0; i < taille; i++) {
		deplacement[a][i] = deplacement[a - 1][i];
	}
	return deplacement;
}

ListeInt **miseAjourCC(ListeInt **ccInitiale, const int taille, int a) {
	int i = 0;
	for(i = 0; i < 6; i++) {
		destructeurListeInt(ccInitiale[a][i]);
		ccInitiale[a][i] = concatenationListeInt(NULL, ccInitiale[a - 1][i]);
	}
	return ccInitiale;
}

int *copieTabInt(int *deplacement, const int taille) {
	int *res = (int*)calloc(taille, sizeof(int));
	int i = 0;
	for(i = 0; i < taille; i++) {
		res[i] = deplacement[i];
	}
	return res;
}

ListeInt **changementCouleurSolveur(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **deplacement, const int taille, int couleur, int nombreCoups) {
	ListeInt ccBonneCouleur = ccPrincipale[nombreCoups][couleur];
	ListeInt save = ccBonneCouleur;
	ccPrincipale[nombreCoups][couleur] = NULL;
	int i = 0;
	int val = 0;
	for(i = 0; i < 6; i++) {
		if(i != couleur) {
			ccPrincipale[nombreCoups][i] = concatenationListeIntDecalage(ccPrincipale[nombreCoups][i], ccPrincipale[nombreCoups - 1][i], deplacement[nombreCoups]);
		}
	}
	while(ccBonneCouleur != NULL) {
		val = ccBonneCouleur->valeur;
		deplacement[nombreCoups][val] = taille + 1;
		for(i = val + 1; i < taille; i++) {
			deplacement[nombreCoups][i] += 1;
		}
		for(i = 0; i < 6; i++) {
			if(i != couleur) {
				ccPrincipale[nombreCoups][i] = concatenationListeIntDecalage(ccPrincipale[nombreCoups][i], tabVoisins[val][i], deplacement[nombreCoups]);
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

int tabVoisinsPlein(int *deplacement, int taille) {
	int i;
	for(i = 0; i < taille; i ++) {
		if(deplacement[i] < taille) {
			return 0;
		}
	}
	return 1;
}

void solveurEtape(ListeInt **tabVoisins, ListeInt **ccPrincipale, int **deplacement, const int taille, int *tailleMax, FILE **f, char *str, int nbrCoups) {
	/*On veut UNE solution en un nombre minimum de coups*/
	deplacement = miseAjour(deplacement, taille, nbrCoups + 1);
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
		else if(estPresentDansListeVerif(deplacement[nbrCoups + 1], taille, listeTest)) {
			return;
		}
		for(i = 0; i < 6; i ++) {
			if(ccPrincipale[nbrCoups][i] != NULL) {
				if (nbrCoups < *tailleMax) {
					ccPrincipale = changementCouleurSolveur(tabVoisins, ccPrincipale, deplacement, taille, i, nbrCoups + 1);

					str[nbrCoups] = conversionEntierChar(i + 1);
					str[nbrCoups + 1] = '\0';
					/*printf("Salut : %s nbrCoups : %d, nombre d'appels récursifs %llu et i : %d\n", str, nbrCoups + 1, nombreAppelsRecursifs, i);
					*//*for(j = 0; j < 6; j ++) {
						afficheListeInt(ccPrincipale[nbrCoups][j]);
					}
					printf("---\n");*/
					solveurEtape(tabVoisins, ccPrincipale, deplacement, taille, tailleMax, f, str, nbrCoups + 1);
					listeTest = constructeurListeVerif(deplacement[nbrCoups + 1], taille, listeTest);
					deplacement = miseAjour(deplacement, taille, nbrCoups + 1);
					ccPrincipale = miseAjourCC(ccPrincipale, taille, nbrCoups + 1);
				}
			}
		}
	}
	return;
}

void solveur(TabComposanteConnexe tabCC, ComposanteConnexe *cc) {
	const int taille = longueurTabComposanteConnexe(tabCC);
	char str[taille + 1];
	int i = 0;
	int j = 0;
	str[0] = '\0';
	ListeInt **tabVoisins = creeTabVoisins(tabCC, taille);
	/*afficheTabVoisins(tabVoisins, taille);*/
	int *tailleMax;
	ListeInt **ccInitiale = (ListeInt **)calloc(taille + 1, sizeof(ListeInt*));
	for(i = 0; i < taille + 1; i ++) {
		ccInitiale[i] = (ListeInt *)calloc(6, sizeof(ListeInt));
	}
	FILE *f = fopen("./solution.txt", "w+");
	tailleMax = calloc(1, sizeof(int));
	int **deplacement = calloc(taille + 1, sizeof(int *));
	for(i = 0; i < taille + 1; i ++) {
		deplacement[i] = calloc(taille, sizeof(int));
	}
	deplacement[0][taille - 1] = taille + 1;
	*tailleMax = taille;

	for(i = 0; i < 6; i ++) {
		ccInitiale[0][i] = concatenationListeInt(ccInitiale[0][i], tabVoisins[taille - 1][i]);
	}
	solveurEtape(tabVoisins, ccInitiale, deplacement, taille, tailleMax, &f, str, 0);
	if(fgets(str, taille, f) != NULL) {
		printf("Solution : %s\n", str);
	}
	printf("Nombre appels %llu\n", nombreAppelsRecursifs);
	for(i = 0; i < taille + 1; i ++) {
		free(deplacement[i]);
	}
	free(deplacement);
	for(i = 0; i < taille + 1; i ++) {
		for(j = 0; j < 6; j ++) {
			destructeurListeInt(ccInitiale[i][j]);
		}
		free(ccInitiale[i]);
	}
	free(ccInitiale);
	fclose(f);
	destructeurListeVerif(listeTest);
	detruitTabVoisins(tabVoisins, taille);
	free(tailleMax);
}