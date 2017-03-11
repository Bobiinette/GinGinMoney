#include "ComposanteConnexe.h"
#include "Grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "colorFlood.h"

#include "ListeComposanteConnexe.h"

/**\file colorFlood.c
 *\brief Execution d'une partie.
 *		Module permettant l'execution d'une partie, mise en place d'une grille de jeu, affichage et déroulement d'une partie.
 */


int main(int argc, char const *argv[])
{
	srand(time(NULL));

	Case **grille;
	Case **grilleTest;
	TabComposanteConnexe tabCC = initTabComposanteConnexe();
	int taille = 0;
	Couleur couleur;
	char choix;
	ComposanteConnexe *cc;

	while(!testTaille(taille)) {
		taille = saisirTaille();
	}

	/*grille = tableauVide(taille);
	grille = remplissageAleatoire(taille, grille);*/
	grilleTest = tableauVide(taille);
	grille = remplissageFichier("./test", 6);
	tabCC = listeComposanteConnexeGrille(grille, taille);
	tabCC = creeVoisins(tabCC, grille, taille);
	cc = rechercheElementTabComposanteConnexeAvecCase(getCaseGrille(grille, 0, 0), tabCC);
	afficheGrille(grille, taille);

	while(!testVictoire(tabCC)) {
		printf("Choix de la couleur : ");
		scanf("%c", &choix);
		couleur = conversionCharCouleur(choix);
		cc = changementCouleur(cc, &tabCC, couleur);
		setGrilleTest(grilleTest, cc);
		afficheGrille(grille, taille);
		/*afficheGrille(grilleTest, taille);*/
		scanf("%c", &choix);
		printf("longueur cases : %d\n", longueurListeCase(getCasesComposanteConnexe(cc)));
		printf("longueur voisins : %d\n", longueurListeComposanteConnexe(getComposantesVoisinesComposanteConnexe(cc)));
		printf("longueur tabCC : %d\n", longueurTabComposanteConnexe(tabCC));
	}

	destructeurTabComposanteConnexe(tabCC);
	liberationGrille(grille, taille);
	liberationGrille(grilleTest, taille);

	return 0;
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
/**\fn int saisirTaille()
 *\brief Demande à l'utilisateur de saisir la taille de la grille de jeu. Cette taille dois être comprise entre 3 et 25.
 *\param aucun paramettre
 *\return la taille de la grille saisi par le joueur.
 */
int saisirTaille() {
	char tmp[3];
	int ret = 0;
	int res = 0;
	int i = 0;

	ret = read(0, tmp, 3*sizeof(char)); /*lit la valeur entrée par le joueur, cette valeur est lu en temps que caractère.*/

	if(ret < 0) {
		perror("Erreur de saisie\n\n");
		return 0;
	}
	else if(ret == 0) {
		printf("Rien n'a été saisi\n\n");
		return 0;
	}
	else if(ret > 3){
		viderBuffer();
		ret = 3;
	}

	for(i = 0; i < ret; i++) {       /*convertie la valeur entrée par le joueur en temps que caractère en un entier*/
		if(tmp[i] > 47 && tmp[i] < 58) {
			res = res * 10 + (tmp[i] - 48);/*48 équivaut au 0*/
		}
	}

	return res;
}
/**\fn int testTaille(int taille)
 *\brief Teste si la taille de grille demandé est bien comprise entre 3 et 25.
 *\param taille Entier qui correspond à la taille demandé pour la grille.
 *\return 1 si la taille est comprise entre 3 et 25, 0 sinon.
 */
int testTaille(int taille) {
	int min = 3;
	int max = 25;
	if(taille < min || taille > max) {
		printf("Merci de rentrer une taille entre %d et %d\n\n", min, max);
		return 0;
	}
	return 1;
}

/**\fn void afficheInterLigneDessus(int taille)
 *\brief Affiche les lignes délimitant les cases du tableau
 *\param taille Entier qui correspond à la taille de la grille.
 */
void afficheInterLigneDessus(int taille) {
	int i = 0;
	for(i = 0;i < taille;i++) {
		printf("----");
	}
	printf("-");
}

/**\fn void afficheInterLigneDessus(int taille)
 *\brief Affiche les cases du tableau
 *\param grille Pointeur vers la grille de jeu.
 *\param taille Entier qui correspond à la taille de la grille.
 *\param ligne Entier qui correspond au numéro de la ligne à afficher.
 */
void afficheLigneDessus(Case **grille, int taille, int ligne) {
	int i = 0;
	for(i = 0;i < taille;i++) { /*affiche pour chaque case de la ligne la couleur et la délimitation de la case */
		printf("|");
		printf(" %c ", (conversionCouleurChar(getCouleurCase(getCaseGrille(grille, ligne, i)))));
	}
	printf("|");
}

/**\fn void afficheGrille(Case **grille, int taille)
 *\brief Affiche la grille en appelant les fonction afficheLigneDessus() et afficheInterLigneDessus().
 *\param grille Pointeur vers la grille de jeu.
 *\param taille Entier qui correspond à la taille de la grille.
 */
void afficheGrille(Case **grille, int taille) {
	int i = 0;

	for(i = 0;i < taille;i++) {
		afficheInterLigneDessus(taille);
		printf("\n");
		afficheLigneDessus(grille, taille, i);
		printf("\n");
	}
	afficheInterLigneDessus(taille);
	printf("\n");
}

void setGrilleTest(Case **grille, ComposanteConnexe *cc) {
	ListeCase tmp = getCasesComposanteConnexe(cc);
	ListeComposanteConnexe voisins = getComposantesVoisinesComposanteConnexe(cc);
	while(!testListeCaseVide(tmp)) {
		setCouleur(getCaseGrille(grille, getXCase(getValeurListeCase(tmp)), getYCase(getValeurListeCase(tmp))), getCouleurCase(getValeurListeCase(tmp)));
		tmp = getSuivantListeCase(tmp);
	}
	while(!estVideListeComposanteConnexe(voisins)) {
		tmp = getCasesComposanteConnexe(getValeurListeComposanteConnexe(voisins));
		while(!testListeCaseVide(tmp)) {
			setCouleur(getCaseGrille(grille, getXCase(getValeurListeCase(tmp)), getYCase(getValeurListeCase(tmp))), getCouleurCase(getValeurListeCase(tmp)));
			tmp = getSuivantListeCase(tmp);
		}

		voisins = getSuivantListeComposanteConnexe(voisins);
	}
}
