#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ListeComposanteConnexe.h"
#include "Grille.h"
#include "solveurTableau.h"

unsigned long long nombreAppelsRecursifs = 0;

struct t_CelluleListeInt {
	int valeur;
	struct t_CelluleListeInt *suivant;
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

int *copieTabInt(int *deplacement, const int taille) {
	int *res = (int*)calloc(taille, sizeof(int));
	int i = 0;
	for(i = 0; i < taille; i++) {
		res[i] = deplacement[i];
	}
	return res;
}

ListeInt *changementCouleurSolveur(ListeInt **tabVoisins, ListeInt *ccPrincipale, int *deplacement, const int taille, int couleur) {
	ListeInt ccBonneCouleur = ccPrincipale[couleur];
	int i = 0;
	int val = 0;
	ListeInt *res = calloc(6, sizeof(ListeInt));
	for(i = 0; i < 6; i++) {
		if(i != couleur) {
			res[i] = concatenationListeIntDecalage(res[i], ccPrincipale[i], deplacement);
		}
		else {
			res[i] = NULL;
		}
	}
	while(ccBonneCouleur != NULL) {
		val = ccBonneCouleur->valeur;
		deplacement[val] = taille + 1;
		for(i = val + 1; i < taille; i++) {
			deplacement[i] += 1;
		}
		for(i = 0; i < 6; i++) {
			res[i] = concatenationListeIntDecalage(res[i], tabVoisins[val][i], deplacement);
		}
		ccBonneCouleur = ccBonneCouleur->suivant;
	}
	return res;
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

void solveurEtape(ListeInt **tabVoisins, ListeInt *ccPrincipale, int *deplacement, const int taille, int *tailleMax, FILE **f, char *str, int nbrCoups) {
	/*On veut UNE solution en un nombre minimum de coups*/
	int i = 0;
	int j = 0;
	nombreAppelsRecursifs += 1;
	int *nouveauDeplacement = NULL;
	ListeInt *nouvelleccPrincipale = NULL;
	int nombreNonNull = 0;

	if(tabVoisins == NULL) {
		fprintf(stderr, "Tab voisins vide\n");
	}
	else {
		nombreNonNull = nombreVoisinsNonNull(ccPrincipale);
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
			free(deplacement);
			for(j = 0; j < 6; j ++) {
				destructeurListeInt(ccPrincipale[j]);
			}
			free(ccPrincipale);
			return;
		}
		/*Un peu d'optimisation ici, si il reste plus de couleurs que de coups restants*/
		else if(nombreNonNull + nbrCoups >= *tailleMax) {
			free(deplacement);
			for(j = 0; j < 6; j ++) {
				destructeurListeInt(ccPrincipale[j]);
			}
			free(ccPrincipale);
			return;
		}
		for(i = 0; i < 6; i ++) {
			if(ccPrincipale[i] != NULL) {
				if (nbrCoups < *tailleMax) {
					nouveauDeplacement = copieTabInt(deplacement, taille);
					nouvelleccPrincipale = changementCouleurSolveur(tabVoisins, ccPrincipale, nouveauDeplacement, taille, i);

					str[nbrCoups] = conversionEntierChar(i + 1);
					str[nbrCoups + 1] = '\0';
					/*printf("Salut : %s nbrCoups : %d, nombre d'appels récursifs %llu et i : %d\n", str, nbrCoups + 1, nombreAppelsRecursifs, i);
					for(j = 0; j < 6; j ++) {
						afficheListeInt(ccPrincipale[j]);
					}
					printf("---\n");*/
					solveurEtape(tabVoisins, nouvelleccPrincipale, nouveauDeplacement, taille, tailleMax, f, str, nbrCoups + 1);
				}
			}
		}
	}
	free(deplacement);
	for(j = 0; j < 6; j ++) {
		destructeurListeInt(ccPrincipale[j]);
	}
	free(ccPrincipale);
	return;
}

void solveur(TabComposanteConnexe tabCC, ComposanteConnexe *cc) {
	const int taille = longueurTabComposanteConnexe(tabCC);
	char str[taille + 1];
	str[0] = '\0';
	ListeInt **tabVoisins = creeTabVoisins(tabCC, taille);
	/*afficheTabVoisins(tabVoisins, taille);*/
	int *tailleMax;
	ListeInt *ccInitiale = (ListeInt *)calloc(6, sizeof(ListeInt));
	FILE *f = fopen("./solution.txt", "w+");
	tailleMax = calloc(1, sizeof(int));
	int *deplacement = calloc(taille, sizeof(int));
	deplacement[taille - 1] = taille + 1;
	*tailleMax = taille;

	int i= 0;
	for(i = 0; i < 6; i ++) {
		ccInitiale[i] = concatenationListeInt(ccInitiale[i], tabVoisins[taille - 1][i]);
	}
	solveurEtape(tabVoisins, ccInitiale, deplacement, taille, tailleMax, &f, str, 0);
	if(fgets(str, taille, f) != NULL) {
		printf("Solution : %s\n", str);
	}
	printf("Nombre appels %llu\n", nombreAppelsRecursifs);
	fclose(f);
	detruitTabVoisins(tabVoisins, taille);
	free(tailleMax);
}