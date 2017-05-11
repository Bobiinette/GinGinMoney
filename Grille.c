#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Grille.h"

struct Case{
    int x;
    int y;
    Couleur couleur;
};


Case * constructeurCase(int x1, int y1, Couleur c){
    Case * res;
	res = (Case *)calloc(1,sizeof(Case));
    res->x=x1;
    res->y=y1;
    res->couleur=c;
    return res;
}


int getXCase(Case *test){
    return test->x;
}


int getYCase(Case *test){
    return test->y;
}


int getCouleurCase(Case *test){
    return test->couleur;
}


void setCouleur(Case *test, Couleur c){
    test->couleur=c;
}


Case ** tableauVide(int n){
    int i;
    int j = 0;
    Case ** res=calloc(n,sizeof(Case *));

    for (i=0;i<n;i++) {
        res[i]=calloc(n,sizeof(Case));
        for(j = 0; j < n; j++) {
            res[i][j].x = i;
            res[i][j].y = j;
        }
    }

    return res;
}


void liberationGrille(Case ** tab, int taille){
    int i;

    for (i=0;i<taille;i++){
            free(tab[i]);
    }
    free(tab);
}


static Couleur aleatoire(){
    Couleur res;

    res=random()%6;
    return res + 1;
}


/*! \fn Case ** remplissageAleatoire(int n, Case **tab)
 *  \brief Fonction de remplissage aléatoire du tableau
 *  \param n est la taille du tableau
 *  \param tab est la grille à remplir
 *  \return renvoie une grille remplie par des couleurs aléatoires
 */
Case ** remplissageAleatoire(int n, Case **tab){
    int i,j;

    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            (tab[i][j]).couleur = aleatoire();
        }
    }
    return tab;
}


static void erreurOuverture(int check){
    if (check){
        perror("Erreur ouverture du fichier. ");
        exit(EXIT_FAILURE);
    }
}


static void erreurLongueur(int check){
    if (check){
        perror("Erreur longueur de la chaîne de caractères dans le fichier ");
        exit(EXIT_FAILURE);
    }
}


static void erreurFinFichier(int check){
    if (check){
        perror("Erreur fin du fichier : tableau non remplie ");
        exit(EXIT_FAILURE);
    }
}


static void checkCouleur(char buff){
    int check = 0;    /*1 si buff est bien une couleur, 0 sinon*/

    check = (buff=='B' || buff=='V' || buff=='R');
    check = (check || buff=='J' || buff=='M' || buff=='G');

    if (!check){
        printf("Erreur couleur inexistante %c ", buff);
        exit(EXIT_FAILURE);
    }
}


Couleur conversionCharCouleur(char c) {
    Couleur couleur = B;
    switch (c) {
        case 'B' :
            couleur = B;
            break;

        case 'R' :
            couleur = R;
            break;

        case 'J' :
            couleur = J;
            break;

        case 'V' :
            couleur = V;
            break;

        case 'M' :
            couleur = M;
            break;

        case 'G' :
            couleur = G;
            break;

        default :
            couleur = B;
            break;
    }
    return couleur;
}



char conversionCouleurChar(Couleur c) {
    char couleur = ' ';
    switch (c) {
        case B :
            couleur = 'B';
            break;

        case R :
            couleur = 'R';
            break;

        case J :
            couleur = 'J';
            break;

        case V :
            couleur = 'V';
            break;

        case M :
            couleur = 'M';
            break;

        case G :
            couleur = 'G';
            break;

        default :
            couleur = ' ';
            break;
    }
    return couleur;
}


char conversionEntierChar(int a) {
    char tmp = 'H';
    switch (a) {
        case 1 :
            tmp = 'B';
            break;

        case 2 :
            tmp = 'V';
            break;

        case 3 :
            tmp = 'R';
            break;

        case 4 :
            tmp = 'J';
            break;

        case 5 :
            tmp = 'M';
            break;

        case 6 :
            tmp = 'G';
            break;

        default :
            tmp = 'H';
            break;
    }
    return tmp;
}


void creationFichier(int n, char * chemin){
	FILE * fichier=NULL;
	int i,j;
	int buff_int;
	char buff_C;

	fichier=fopen(chemin,"w+");
	erreurOuverture(fichier==NULL);

	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			buff_int=aleatoire();
			buff_C=conversionEntierChar(buff_int);
			fputc(buff_C,fichier);
		}
		fputc('\n',fichier);
	}
}


Case ** remplissageFichier(char * chemin, int taille){
    FILE * fichier=NULL;
    char buff;
    int i,j;
    Case ** res = tableauVide(taille);

    fichier=fopen(chemin,"r");
    erreurOuverture(fichier==NULL);

    for (i=0;i<taille;i++){
        for (j=0;j<taille;j++){
            buff=fgetc(fichier);
            erreurLongueur(buff=='\n');    /*vérifie la longueur de la chaine de caractères en cours de lecture*/
            erreurFinFichier(buff==EOF); /*vérifie qu'on n'est pas à la fin du fichier*/
            if(buff!='\n') {
                checkCouleur(buff);    /*vérifie si la couleur existe*/
                res[i][j].couleur=conversionCharCouleur(buff);
            }
        }
        fgetc(fichier);    /*lit le caractère "\n" après chaque fin de ligne*/
    }

    fclose(fichier);
    return res;
}


Case * getCaseGrille(Case ** grille, int i, int j) {
    return &(grille[i][j]);
}
