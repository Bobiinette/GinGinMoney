#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ListeComposanteConnexe.h"
#include "Grille.h"
#include "solveurTableau3.h"

/**\file solveurTableau3.c
 *\brief Solveur à base de tableaux d'entiers
 *	Solution proposée pour le solveur, à base de tableaux de listes d'entiers.
 *	On attribue ici un numéro à chaque composante connexe, et on voit une composante connexe comme un tableau avec 1 colonne et 6 lignes, chaque ligne représantant une couleur de la composante connexe.
 *	Dans chaque ligne, on a une liste de voisins correspondant aux voisins de la composante connexe, avec la couleur correspondant à la ligne sélectionnée.
 */

/*======================================================= CODE ==========================================================*/

int nombreVoisinsCouleur(ListeInt** tabVoisins, ListeInt* ccPrincipale, int* appartenance, int couleur, const int taille) {
	int traites[taille];
	int i = 0;
	for(i = 0; i < taille; i++) {
		traites[i] = appartenance[i];
		/*printf("%d", traites[i]);*/
	}
	/*printf("\n");*/
	ListeInt tmp = ccPrincipale[couleur];
	ListeInt tmp2 = NULL;
	int res = 0;
	int nb = 0;
	int nb2 = 0;
	res -= longueurListeInt(tmp);

	while (tmp != NULL) {
		nb = getValeurListeInt(tmp);
		if(traites[nb] == 0) {
			for(i = 0; i < 6; i ++) {
				tmp2 = tabVoisins[nb][i];
				while(tmp2 != NULL) {
					nb2 = getValeurListeInt(tmp2);
					if(traites[nb2] == 0) {
						res = res + 1;
						traites[nb2] = 1;
					}
					tmp2 = getSuivantListeInt(tmp2);
				} 
			}
			traites[nb] = 1;
		}
		tmp = getSuivantListeInt(tmp);
	}
	return res;
}


int couleurAChoisir(ListeInt** tabVoisins, ListeInt* ccPrincipale, int* appartenance, const int taille) {
	int i = 0;
	int couleurMax = 0;
	int max = 0;
	int a = 0;
	for(i = 0; i < 6; i ++) {
		a = nombreVoisinsCouleur(tabVoisins, ccPrincipale, appartenance, i, taille);
		if(a > max && ccPrincipale[i] != NULL) {
			max = a;
			couleurMax = i;
		}
		else if(max > a && ccPrincipale[couleurMax] == NULL) {
			max = a;
			couleurMax = i;
		}
		afficheListeInt(ccPrincipale[i]);
	}
	return couleurMax;
}

int couleurAChoisir2(ListeInt** tabVoisins, ListeInt* ccPrincipale, int* appartenance, const int taille) {
	int i = 0;
	int couleurMax = 0;
	int max = 0;
	int a = 0;
	for(i = 0; i < 6; i ++) {
		a = nombreVoisinsCouleur(tabVoisins, ccPrincipale, appartenance, i, taille);
		if(a > max && ccPrincipale[i] != NULL) {
			max = a;
			couleurMax = i;
		}
		else if(max > a && ccPrincipale[couleurMax] == NULL) {
			max = a;
			couleurMax = i;
		}
		afficheListeInt(ccPrincipale[i]);
	}
	return couleurMax;
}

ListeInt *changementCouleurSolveur3(ListeInt **tabVoisins, ListeInt *ccPrincipale, int *appartenance, const int taille, int couleur) {
	ListeInt ccBonneCouleur = ccPrincipale[couleur];
	ListeInt save = ccBonneCouleur;
	ccPrincipale[couleur] = NULL;
	ListeInt *res = calloc(taille, sizeof(ListeInt));
	int i = 0;
	int val = 0;
	for(i = 0; i < 6; i++) {
		if(i != couleur) {
			res[i] = concatenationListeIntTestAppartenance(res[i], ccPrincipale[i], appartenance);
		}
	}
	while(ccBonneCouleur != NULL) {
		val = getValeurListeInt(ccBonneCouleur);
		appartenance[val] = 1;
		for(i = 0; i < 6; i++) {
			if(i != couleur) {
				res[i] = concatenationListeIntTestAppartenance(res[i], tabVoisins[val][i], appartenance);
			}
		}
		ccBonneCouleur = getSuivantListeInt(ccBonneCouleur);
	}
	destructeurListeInt(save);
	return res;
}

char* solveurEtape3(ListeInt **tabVoisins, ListeInt *ccPrincipale, int *appartenance, const int taille, char *str) {
	int couleur = 0;
	int nbrCoups = 0;
	while(nombreVoisinsNonNull(ccPrincipale) != 0) {
		couleur = couleurAChoisir(tabVoisins, ccPrincipale, appartenance, taille);
		printf("COULEUR : %d\n", couleur);
		ccPrincipale = changementCouleurSolveur3(tabVoisins, ccPrincipale, appartenance, taille, couleur);
		str[nbrCoups] = conversionEntierChar(couleur + 1);
		str[nbrCoups + 1] = '\0';
		nbrCoups += 1;
	}
	return str;
}

int solveurTableau3(TabComposanteConnexe tabCC, ComposanteConnexe *cc) {
	const int taille = longueurTabComposanteConnexe(tabCC);
	char *str = malloc(taille + 1);
	int i = 0;
	int j = 0;
	str[0] = '\0';
	ListeInt **tabVoisins = creeTabVoisins(tabCC, taille);
	/*afficheTabVoisins(tabVoisins, taille);*/
	int res = 0;
	ListeInt *ccInitiale = (ListeInt *)calloc(taille, sizeof(ListeInt*));
	FILE *f = fopen("./solutionTableau.txt", "w+");
	int *appartenance = calloc(taille, sizeof(int));
	appartenance[taille - 1] = 1;

	for(i = 0; i < 6; i ++) {
		ccInitiale[i] = NULL;
		ccInitiale[i] = concatenationListeInt(ccInitiale[i], tabVoisins[taille - 1][i]);
	}


	str = solveurEtape3(tabVoisins, ccInitiale, appartenance, taille, str);

	res = strlen(str);

	if(str != NULL) {
		printf("Solution : %s\n", str);
	}
	free(appartenance);
	for(j = 0; j < 6; j ++) {
		destructeurListeInt(ccInitiale[j]);
	}
	free(str);
	free(ccInitiale);
	fclose(f);
	detruitTabVoisins(tabVoisins, taille);
	return res;
}