#ifndef GRILLE_H
#define GRILLE_H

typedef enum Couleur {H = 0,B,V,R,J,M,G} Couleur;

/*! \struct Case
 *  \brief Structure de cases.
 */
typedef struct Case Case;

/*! \fn Case * constructeurCase(int x1, int y1, Couleur c)
 *  \brief Construit une case à partir de coordonnées et d'une couleur données
 *  \param x1 est l'abscisse de la case
 *  \param y1 est l'ordonnée de la case
 *  \param c est la couleur de la case
 *  \return renvoie la case correspondante
 */
Case * constructeurCase(int x1, int y1, Couleur c);

/*! \fn int getXCase(Case *test)
 *  \brief Récupère l'abscisse de la case considérée
 *  \param test est la case dont on veut connaitre l'abscisse
 *  \return renvoie l'abscisse correspondante
 */
int getXCase(Case *test);

/*! \fn int getYCase(Case *test)
 *  \brief Récupère l'ordonnée de la case considérée
 *  \param test est la case dont on veut connaitre l'ordonnée
 *  \return renvoie l'ordonnée correspondante
 */
int getYCase(Case *test);

/*! \fn int getCouleurCase(Case *test)
 *  \brief Récupère la couleur de la case considérée
 *  \param test est la case dont on veut connaitre la couleur
 *  \return renvoie la couleur correspondante
 */
int getCouleurCase(Case *test);

/*! \fn void setCouleur(Case *test, Couleur c)
 *  \brief Change la couleur de la case considérée par la couleur en paramètre
 *  \param test est la case dont on veut changer la couleur
 *  \param c est la couleur que l'on souhaiterait mettre
 */
void setCouleur(Case *test, Couleur c);

/*! \fn Case ** tableauVide(int n)
 *  \brief Initialise un tableau vide de taille n
 *  \param n est la taille du tableau
 *  \return renvoie un tableau vide de taille n
 */
Case ** tableauVide(int n);

/*! \fn void liberationGrille(Case ** tab, int taille)
 *  \brief Libère l'espace mémoire occupé par la grille
 *  \param tab est la grille qui occupe la mémoire
 *  \param taille est la taille de cette grille
 */
void liberationGrille(Case ** tab, int taille);

/*! \fn static Couleur aleatoire()
 *  \brief Renvoie une couleur aléatoirement
 *  \return Une couleur aléatoire
 */
static Couleur aleatoire();

/*! \fn Case ** remplissageAleatoire(int n, Case **tab)
 *  \brief Fonction de remplissage aléatoire du tableau
 *  \param n est la taille du tableau
 *  \param tab est la grille à remplir
 *  \return renvoie une grille remplie par des couleurs aléatoires
 */
Case ** remplissageAleatoire(int n, Case **tab);

/*! \fn static void erreurOuverture(int check)
 *  \brief Vérifie qu'il n'y a pas d'erreur d'ouverture du fichier : si ce n'est pas le cas, le programme s'arrête avec une erreur
 *  \param check est la vérification à faire
 */
static void erreurOuverture(int check);

/*! \fn static void erreurLongueur(int check)
 *  \brief Vérifie la longueur des chaines de caractères dans le fichier : si ce n'est pas le cas, le programme s'arrête avec une erreur
 *  \param check est la vérification à faire
 */
static void erreurLongueur(int check);

/*! \fn static void erreurFinFichier(int check)
 *  \brief Vérifie qu'on n'est pas à la fin du fichier : si ce n'est pas le cas, le programme s'arrête avec une erreur
 *  \param check est la vérification à faire
 */
static void erreurFinFichier(int check);

/*! \fn static void checkCouleur(char buff)
 *  \brief Vérifie que la couleur existe : si ce n'est pas le cas, le programme s'arrête avec une erreur
 *  \param buff est le caractère à vérifier
 */
static void checkCouleur(char buff);

/*! \fn Couleur conversionCharCouleur(char c)
 *  \brief Transforme un char en couleur
 *  \param c est la couleur de type char à transformer en type Couleur
 *  \return Renvoie la couleur correspondante
 */
Couleur conversionCharCouleur(char c);

/*! \fn char conversionCouleurChar(Couleur c)
 *  \brief Transforme une couleur en char
 *  \param c est la couleur à transformer en type char
 *  \return Renvoie le char correspondant
 */
char conversionCouleurChar(Couleur c);

/*! \fn char conversionCouleurChar(int a)
 *  \brief Transforme un entier en char
 *  \param a est l'entier à transformer en type char
 *  \return Renvoie le char correspondant
 */
char conversionEntierChar(int a);

/*! \fn void creationFichier(int n, char * chemin)
 *  \brief Ecrit dans le fichier mis en paramètre n suites de n lettres aléatoires (B,V,R,J,M,G)
 *  \param n est la taille de la grille
 *  \param chemin est le chemin où se trouve le fichier où contiendra les suites de chiffres
 */
void creationFichier(int n, char * chemin);

/*! \fn Case ** remplissageFichier(char * chemin, int taille)
 *  \brief Fonction de remplissage aléatoire du tableau (le fichier doit contenir n suites de n chiffres aléatoires entre 0 et 5)
 *  \param chemin donne le chemin d'accès au fichier
 *  \param taille est la taille de la future grille
 *  \return Renvoie la grille obtenue par lecture de fichier
 */
Case ** remplissageFichier(char * chemin, int taille);

/*! \fn Case * getCaseGrille(Case ** grille, int i, int j)
 *  \brief Renvoie un pointeur vers une case
 *  \param grille est la grille du jeu
 *  \param i est l'abscisse de la case
 *  \param j est l'ordonnée de la case
 *  \return renvoie un pointeur vers la case grille[i][j]
 */
Case * getCaseGrille(Case ** grille, int i, int j);

#endif
