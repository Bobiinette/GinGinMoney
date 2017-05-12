#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ListeComposanteConnexe.h"
#include "solveur.h"
#include "Grille.h"

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

/*La liste l1 n'est pas modifiée*/
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

ListeInt **changementCouleurSolveur(ListeInt **tabVoisins, int taille, int* nouvelleTaille, Couleur nouvelleCouleur) {
	ListeInt colonesAEnlever = initListeInt();
	ListeInt **res = NULL;

	colonesAEnlever = tabVoisins[taille - 1][nouvelleCouleur - 1];

	*nouvelleTaille = taille - longueurListeInt(colonesAEnlever);
	res = supprimeColone(tabVoisins, taille, *nouvelleTaille, colonesAEnlever);

	return res;
}

ListeInt additionScalaireListeInt(ListeInt l, int n) {
	ListeInt tmp = l;
	while(l != NULL) {
		l->valeur = l->valeur + n;
		l = l->suivant;
	}
	return tmp;
}

ListeInt triListeInt(ListeInt l) {
	ListeInt tmp = l;
	ListeInt i = l;
	int min = 0;
	ListeInt position = NULL;
	while(tmp != NULL) {
		i = tmp;
		min = tmp->valeur;
		position = tmp;
		while(i != NULL) {
			if(i->valeur < min) {
				min = i->valeur;
				position = i;
			}
			i = i->suivant;
		}
		position->valeur = tmp->valeur;
		tmp->valeur = min;
		tmp = tmp->suivant;
	}
	return l;
}

ListeInt gestionDecalage(ListeInt l, int valeurTest, int valeurASupprimer) {
	ListeInt tmp = l;
	while(tmp != NULL) {
		if(tmp->valeur > valeurTest) {
			tmp->valeur = tmp->valeur - 1;
			if(tmp->valeur == valeurASupprimer) {
				tmp->valeur = -1;
			}
		}
		else if(tmp->valeur == valeurTest) {
			tmp->valeur = -1;
		}
		tmp = tmp->suivant;
	}
	return l;
}

ListeInt **supprimeColone(ListeInt **tabVoisins, int taille, int nouvelleTaille, ListeInt colonesAEnlever) {
	ListeInt **res = NULL;
	ListeInt tmp = colonesAEnlever;
	int deplacement = 0;
	int i = 0;
	int j = 0;


	res = (ListeInt**)calloc(nouvelleTaille, sizeof(ListeInt*));
	for(i = 0; i < nouvelleTaille; i++) {
		res[i] = (ListeInt*)calloc(6, sizeof(ListeInt));
		for(j = 0; j < 6; j++) {
			res[i][j] = NULL;
		}
	}
	
	for(i = 0; i < taille; i ++) {
		if(!estPresentDansListeInt(i, colonesAEnlever)) {
			for(j = 0; j < 6; j ++) {
				res[i - deplacement][j] = concatenationListeInt(res[i - deplacement][j], tabVoisins[i][j]);
			}
		}
		else {
			for(j = 0; j < 6; j ++) {
				res[nouvelleTaille - 1][j] = concatenationListeInt(res[nouvelleTaille - 1][j], tabVoisins[i][j]);
			}
			deplacement ++;
		}
	}

	colonesAEnlever = triListeInt(colonesAEnlever);
	tmp = colonesAEnlever;
	deplacement = 0;

	while(tmp != NULL) {
		for(i = 0; i < nouvelleTaille; i++) {
			for(j = 0; j < 6; j ++) {
				res[i][j] = gestionDecalage(res[i][j], tmp->valeur - deplacement, nouvelleTaille - 1);
			}
		}
		tmp = tmp->suivant;
		deplacement ++;
	}

	
	return res;
}

int testNull(ListeInt * tab) {
	int i = 0;
	for(i = 0; i < 6; i++) {
		if(longueurListeInt(tab[i]) > 0) {
			return 0;
		}
	}
	return 1;
}

void solveurEtape(ListeInt **tabVoisins, int taille, int *tailleMax, FILE **f, char *str, int nbrCoups) {
	/*On veut UNE solution en un nombre minimum de coups*/
	if(tabVoisins == NULL) {
		fprintf(stderr, "Tab voisins vide\n");
	}
	else if(nbrCoups >= *tailleMax) {
		detruitTabVoisins(tabVoisins, taille);
		return;
	}
	else if(taille == 1) {
		if(testNull(tabVoisins[taille - 1])) {
			if(nbrCoups < *tailleMax) {
				*tailleMax = nbrCoups;
				fclose(*f);
				*f = fopen("./solution.txt", "w+");
			}
			printf("Nouvelle solution en %d coups\n", nbrCoups);
			fputs(str, *f);
			fputc('\n', *f);
		}
		detruitTabVoisins(tabVoisins, taille);
		return;
	}
	else if(taille < 1) {
		detruitTabVoisins(tabVoisins, taille);
		return;
	}
	else {
		int i = 0;
		int nombreNull = 0;
		for(i = 0; i < 6; i ++) {
			if(longueurListeInt(tabVoisins[taille - 1][i]) > 0) {
				int *nouvelleTaille = (int *)calloc(1, sizeof(int));
				ListeInt **nouveauTabVoisins = changementCouleurSolveur(tabVoisins, taille, nouvelleTaille, i + 1);

				str[nbrCoups] = conversionEntierChar(i + 1);
				str[nbrCoups + 1] = '\0';

				destructeurListeInt(tabVoisins[*nouvelleTaille - 1][i]);
				tabVoisins[*nouvelleTaille - 1][i] = NULL;

				/*afficheTabVoisins(nouveauTabVoisins, *nouvelleTaille);*/

				solveurEtape(nouveauTabVoisins, *nouvelleTaille, tailleMax, f, str, nbrCoups + 1);

				/*detruitTabVoisins(nouveauTabVoisins, *nouvelleTaille);*/
				free(nouvelleTaille);
				nombreNull ++;
			}
		}
		if(nombreNull == 0) {
			/*fprintf(stderr, "6 NOMBRES NULL LES ENFANTS\n");*/
			detruitTabVoisins(tabVoisins, taille);
			return;
		}
	}
	detruitTabVoisins(tabVoisins, taille);
	return;
}

void solveur(TabComposanteConnexe tabCC, ComposanteConnexe *cc) {
	const int taille = longueurTabComposanteConnexe(tabCC);
	char str[taille + 1];
	ListeInt **tabVoisins = creeTabVoisins(tabCC, taille);
	/*afficheTabVoisins(tabVoisins, taille);*/
	int *tailleMax;
	FILE *f = fopen("./solution.txt", "w+");
	tailleMax = calloc(1, sizeof(int));
	*tailleMax = taille;
	solveurEtape(tabVoisins, taille, tailleMax, &f, str, 0);
	fclose(f);
	/*detruitTabVoisins(tabVoisins, taille);*/
	free(tailleMax);
}