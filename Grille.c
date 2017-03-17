#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Grille.h"

/*! \struct Case
 *  \brief Structure de cases.
 */
struct Case{
    int x;
    int y;
    Couleur couleur;
};


/*! \fn Case * constructeurCase(int x1, int y1, Couleur c)
 *  \brief Construit une case à partir de coordonnées et d'une couleur données
 *  \param x1 est l'abscisse de la case
 *  \param y1 est l'ordonnée de la case
 *  \param c est la couleur de la case
 *  \return renvoie la case correspondante
 */
Case * constructeurCase(int x1, int y1, Couleur c){
    Case * res;
	res = (Case *)calloc(1,sizeof(Case));
    res->x=x1;
    res->y=y1;
    res->couleur=c;
    return res;
}


/*! \fn int getXCase(Case *test)
 *  \brief Récupère l'abscisse de la case considérée
 *  \param test est la case dont on veut connaitre l'abscisse
 *  \return renvoie l'abscisse correspondante
 */
int getXCase(Case *test){
    return test->x;
}


/*! \fn int getYCase(Case *test)
 *  \brief Récupère l'ordonnée de la case considérée
 *  \param test est la case dont on veut connaitre l'ordonnée
 *  \return renvoie l'ordonnée correspondante
 */
int getYCase(Case *test){
    return test->y;
}


/*! \fn int getCouleurCase(Case *test)
 *  \brief Récupère la couleur de la case considérée
 *  \param test est la case dont on veut connaitre la couleur
 *  \return renvoie la couleur correspondante
 */
int getCouleurCase(Case *test){
    return test->couleur;
}


/*! \fn void setCouleur(Case *test, Couleur c)
 *  \brief Change la couleur de la case considérée par la couleur en paramètre
 *  \param test est la case dont on veut changer la couleur
 *  \param c est la couleur que l'on souhaiterait mettre
 */
void setCouleur(Case *test, Couleur c){
    test->couleur=c;
}


/*! \fn Case ** tableauVide(int n)
 *  \brief Initialise un tableau vide de taille n
 *  \param n est la taille du tableau
 *  \return renvoie un tableau vide de taille n
 */
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


/*! \fn void liberationGrille(Case ** tab, int taille)
 *  \brief Libère l'espace mémoire occupé par la grille
 *  \param tab est la grille qui occupe la mémoire
 *  \param taille est la taille de cette grille
 */
void liberationGrille(Case ** tab, int taille){
    int i;

    for (i=0;i<taille;i++){
            free(tab[i]);
    }
    free(tab);
}


/*! \fn static Couleur aleatoire()
 *  \brief Renvoie une couleur aléatoirement
 *  \return Une couleur aléatoire
 */
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


/*! \fn static void erreurOuverture(int check)
 *  \brief Vérifie qu'il n'y a pas d'erreur d'ouverture du fichier : si ce n'est pas le cas, le programme s'arrête avec une erreur
 *  \param check est la vérification à faire
 */
static void erreurOuverture(int check){
    if (check){
        perror("Erreur ouverture du fichier. ");
        exit(EXIT_FAILURE);
    }
}


/*! \fn static void erreurLongueur(int check)
 *  \brief Vérifie la longueur des chaines de caractères dans le fichier : si ce n'est pas le cas, le programme s'arrête avec une erreur
 *  \param check est la vérification à faire
 */
static void erreurLongueur(int check){
    if (check){
        perror("Erreur longueur de la chaîne de caractères dans le fichier ");
        exit(EXIT_FAILURE);
    }
}


/*! \fn static void erreurFinFichier(int check)
 *  \brief Vérifie qu'on n'est pas à la fin du fichier : si ce n'est pas le cas, le programme s'arrête avec une erreur
 *  \param check est la vérification à faire
 */
static void erreurFinFichier(int check){
    if (check){
        perror("Erreur fin du fichier : tableau non remplie ");
        exit(EXIT_FAILURE);
    }
}


/*! \fn static void checkCouleur(char buff)
 *  \brief Vérifie que la couleur existe : si ce n'est pas le cas, le programme s'arrête avec une erreur
 *  \param buff est le caractère à vérifier
 */
static void checkCouleur(char buff){
    int check = 0;    /*1 si buff est bien une couleur, 0 sinon*/

    check = (buff=='B' || buff=='V' || buff=='R');
    check = (check || buff=='J' || buff=='M' || buff=='G');

    if (!check){
        printf("Erreur couleur inexistante %c ", buff);
        exit(EXIT_FAILURE);
    }
}


/*! \fn Couleur conversionCharCouleur(char c)
 *  \brief Transforme un char en couleur
 *  \param c est la couleur de type char à transformer en type Couleur
 *  \return Renvoie la couleur correspondante
 */
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


/*! \fn char conversionCouleurChar(int a)
 *  \brief Transforme un entier en char
 *  \param a est l'entier à transformer en type char
 *  \return Renvoie le char correspondant
 */
char conversionEntierChar(int a) {
    char tmp = 'B';
    switch (a) {
        case 0 :
            tmp = 'B';
            break;

        case 1 :
            tmp = 'V';
            break;

        case 2 :
            tmp = 'R';
            break;

        case 3 :
            tmp = 'J';
            break;

        case 4 :
            tmp = 'M';
            break;

        case 5 :
            tmp = 'G';
            break;

        default :
            tmp = 'B';
            break;
    }
    return tmp;
}


/*! \fn void creationFichier(int n, char * chemin)
 *  \brief Ecrit dans le fichier mis en paramètre n suites de n lettres aléatoires (B,V,R,J,M,G)
 *  \param n est la taille de la grille
 *  \param chemin est le chemin où se trouve le fichier où contiendra les suites de chiffres
 */
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



/*! \fn Case ** remplissageFichier(char * chemin, int taille)
 *  \brief Fonction de remplissage aléatoire du tableau (le fichier doit contenir n suites de n chiffres aléatoires entre 0 et 5)
 *  \param chemin donne le chemin d'accès au fichier
 *  \param taille est la taille de la future grille
 *  \return Renvoie la grille obtenue par lecture de fichier
 */
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


/*! \fn Case * getCaseGrille(Case ** grille, int i, int j)
 *  \brief Renvoie un pointeur vers une case
 *  \param grille est la grille du jeu
 *  \param i est l'abscisse de la case
 *  \param j est l'ordonnée de la case
 *  \return renvoie un pointeur vers la case grille[i][j]
 */
Case * getCaseGrille(Case ** grille, int i, int j) {
    return &(grille[i][j]);
}
