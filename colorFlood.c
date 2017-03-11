#include "ComposanteConnexe.h"
#include "Grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "colorFlood.h"
#include <termios.h>
#include "ListeComposanteConnexe.h"

/**\file colorFlood.c
 *\brief Execution d'une partie.
 *		Module permettant l'execution d'une partie, mise en place d'une grille de jeu, affichage et déroulement d'une partie.
 */


int main()
{
	srand(time(NULL));

	Case **grille;
	Case **grilleTest;
	TabComposanteConnexe tabCC;
	int taille = 0;
	int nbrCoups = 0;
	Couleur couleur;
	char choix;
	ComposanteConnexe *cc;

	while(!testTaille(taille)) {
		taille = saisirTaille();
	}
	printf("Entrez le nombre de coups que vous pensez effectuer\n");
	nbrCoups=saisirTaille();
	/*grille = tableauVide(taille);
	grille = remplissageAleatoire(taille, grille);*/
	grilleTest = tableauVide(taille);
	grille = remplissageFichier("./test", 6);
	tabCC = listeComposanteConnexeGrille(grille, taille);
	tabCC = creeVoisins(tabCC, grille, taille);
	cc = rechercheElementTabComposanteConnexeAvecCase(getCaseGrille(grille, 0, 0), tabCC);
	afficheGrille(grille, taille);

	while(!testVictoire(tabCC) && nbrCoups!=0) {
		choix=saisirCouleur(nbrCoups);
		nbrCoups= nbrCoups -1;
		couleur = conversionCharCouleur(choix);
		cc = changementCouleur(cc, &tabCC, couleur);
		setGrilleTest(grilleTest, cc);
		afficheGrille(grille, taille);
		afficheGrille(grilleTest, taille);
		printf("longueur cases : %d\n", longueurListeCase(getCasesComposanteConnexe(cc)));
		printf("longueur voisins : %d\n", longueurListeComposanteConnexe(getComposantesVoisinesComposanteConnexe(cc)));
		printf("longueur tabCC : %d\n", longueurTabComposanteConnexe(tabCC));
	}
	if (nbrCoups == 0){
		printf("Dommage, vous avez perdu\n");
	}
	else{
		printf("Bravo!!! Vous avez gagner!!!!!\n");
	}
	destructeurTabComposanteConnexe(tabCC);
	liberationGrille(grille, taille);

	return 0;
}
/**\fn int getche(void)
*\brief C'est la fonction qui permet de gèrer ce que tape l'utilisateur sur le clavier
*\return la valeur entrée par l'utilisateur au clavier
*/
int getche(void) {
	struct termios oldattr, newattr;
	int ch;
	tcgetattr( STDIN_FILENO, &oldattr );
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
	return ch;
}

/**\fn char saisirCouleur()
*\brief Cette fonction vérifie que la couleur demandé existe.
*\return la valeur correspondant à une couleur existante entrée par l'utilisateur au clavier
*/
char saisirCouleur(int nbrCoup){
	char c;
	printf("Il vous reste %d coups restant\n",nbrCoup);
	printf ("Choisissez votre couleur : J pour jaune, B pour bleu, R pour rouge, M pour Marron, V pour vert et G pour gris\n");
	printf("Choix de la couleur : ");
	c=getche();
	while (c!='j' && c!='J' && c!='r' && c!='R' && c!='m' && c!='M' && c!='b' && c!='B' && c!='g' && c!='G' && c!='v' && c!='V'){
		printf ("Cette couleur n'existe pas. Choisissez votre couleur : J pour jaune, B pour bleu, R pour rouge, M pour Marron, V pour vert et G pour gris\n");
		c=getche();
	}
	switch (c) {
		case 'j':
			return 'J';
		case 'r':
			return 'R';
		case 'm':
			return 'M';
		case 'b':
			return 'B';
		case 'g':
			return 'G';
		case 'v':
			return 'V';
		default :
			return c;
	}
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
	printf("Composante actuelle\n");
	while(!testListeCaseVide(tmp)) {
		setCouleur(getCaseGrille(grille, getXCase(getValeurListeCase(tmp)), getYCase(getValeurListeCase(tmp))), getCouleurCase(getValeurListeCase(tmp)));
		printf("x : %d|| y : %d\n", getXCase(getValeurListeCase(tmp)), getYCase(getValeurListeCase(tmp)));
		tmp = getSuivantListeCase(tmp);
	}
	while(!estVideListeComposanteConnexe(voisins)) {
		tmp = getCasesComposanteConnexe(getValeurListeComposanteConnexe(voisins));
		printf("Nouveau voisin\n");
		while(!testListeCaseVide(tmp)) {
			setCouleur(getCaseGrille(grille, getXCase(getValeurListeCase(tmp)), getYCase(getValeurListeCase(tmp))), getCouleurCase(getValeurListeCase(tmp)));
			printf("x : %d|| y : %d\n", getXCase(getValeurListeCase(tmp)), getYCase(getValeurListeCase(tmp)));
			tmp = getSuivantListeCase(tmp);
		}

		voisins = getSuivantListeComposanteConnexe(voisins);
	}
}
