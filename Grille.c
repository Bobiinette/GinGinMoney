#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Grille.h"

struct Case{
    int x;
    int y;
    Couleur couleur;
};

/**\brief Récupère l'abscisse de la case considérée**/
int getXCase(Case *test){
    return test->x;
}

/**\brief Récupère l'ordonnée de la case considérée**/
int getYCase(Case *test){
    return test->y;
}

/**\brief Récupère la couleur de la case considérée**/
int getCouleurCase(Case *test){
    return test->couleur;
}

/**\brief Change la couleur de la case considérée par la couleur en paramètre**/
void setCouleur(Case *test, Couleur c){
    test->couleur=c;
}

/**\brief Initialise un tableau vide de taille n**/
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


/**\brief Libère l'espace mémoire occupé par la grille**/
void liberationGrille(Case ** tab, int taille){
    int i;

    for (i=0;i<taille;i++){
            free(tab[i]);
    }
    free(tab);
}


/**\brief Renvoie une couleur aléatoirement**/
static Couleur aleatoire(){
    Couleur res;

    res=random()%6;
    return res;
}

/**\brief Fonction de remplissage aléatoire du tableau**/
Case ** remplissageAleatoire(int n, Case **tab){
    int i,j;

    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            (tab[i][j]).couleur = aleatoire();
        }
    }
    return tab;
}


/**\brief Fonction de remplissage du tableau à partir d'un fichier**/
static void erreurOuverture(int check){
    if (check){
        perror("Erreur ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
}


/**\brief Vérifie la longueur des chaines de caractères dans le fichier**/
static void erreurLongueur(int check){
    if (check){
        perror("Erreur longueur de la chaîne de caractères dans le fichier.\n");
        exit(EXIT_FAILURE);
    }
}


/**\brief Vérifie qu'on n'est pas à la fin du fichier**/
static void erreurFinFichier(int check){
    if (check){
        perror("Erreur fin du fichier : tableau non remplie.\n");
        exit(EXIT_FAILURE);
    }
}


/**\brief Vérifie que la couleur existe**/
static void checkCouleur(char buff){
    int check = 0;    /*1 si buff est bien une couleur, 0 sinon*/

    check = (buff=='B' || buff=='V' || buff=='R');
    check = (check || buff=='J' || buff=='M' || buff=='G');

    if (!check){
        printf("Erreur couleur inexistante %c.\n", buff);
        exit(EXIT_FAILURE);
    }
}


/*@requires Le fichier contient des chaines de caractères contenant un retour à la ligne au bout de chaque ligne
    @ensures Crée un tableau de couleur à partir d'un fichier*/
Case ** remplissageFichier(char * text, int taille/*taille de la grille*/){/*On crée un tableau vide dans cette fonction!!!!!!!!!!!!!!*/
    FILE * fichier=NULL;
    int lecture;    /*lecture caractère par caractère dans le fichier*/
    char buff;
    int k=0; /*variable permettant de déterminer la longueur de la première ligne et d'en déduire la taille*/ 
    int i,j;
    Case ** res = tableauVide(taille);

    fichier=fopen(text,"r");
    erreurOuverture(fichier==NULL);

    for (i=0;i<taille;i++){ /*remplissage du tableau*/
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

Case *** pointeurVersGrille(Case **grille, int taille) {
    int i = 0;
    int j = 0;
    Case ***pGrille = NULL;
    pGrille = calloc(taille, sizeof(Case **));
    for(i = 0; i < taille; i ++) {
        pGrille[i] = calloc(taille, sizeof(Case *));
        for(j = 0; j < taille; j ++) {
            pGrille[i][j] = grille[i] + j;
            printf("%d", getCouleurCase(pGrille[i][j]));
        }
        printf("\n");
    }
}

void destructeurPointeurVersGrille(Case *** pGrille, int taille) {
    int i = 0;
    int j = 0;
    for(i = 0; i < taille; i ++) {
        free(pGrille[i]);
    }
    free(pGrille);
    pGrille = NULL;
}

Case * getCaseGrille(Case ** grille, int i, int j) {
    return &(grille[i][j]);
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

