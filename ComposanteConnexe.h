#ifndef COMPOSANTE_CONNEXE_H
#define COMPOSANTE_CONNEXE_H
/**\file ComposanteConnexe.h
 *\brief Gestion des composantes connexes.
 *		Module permettant la gestion des composantes connexes, et d'une liste de composante connexe (sans pointeurs).
 */

 /**\struct ComposanteConnexe ComposanteConnexe.h
  *\brief Structure de composante connexe.
  */
typedef struct ComposanteConnexe ComposanteConnexe;

/**\struct TabComposanteConnexe ComposanteConnexe.h
 *\brief Structure de liste de composante connexe.
 */
typedef struct t_CelluleTabComposanteConnexe CelluleTabComposanteConnexe;
typedef CelluleTabComposanteConnexe *TabComposanteConnexe;

#include "ListeComposanteConnexe.h"
#include "Grille.h"
#include "Cases.h"

/**\fn CompoanteConnexe initComposanteConnexe (void)
 *\brief Initialise une composante connexe à NULL
 *\param void
 *\return ComposanteConnexe initialisée à NULL, et couleur bleu
 */
ComposanteConnexe initComposanteConnexe();

/**\fn ComposanteConnexe constructeurComposanteConnexe(Case *emplacementInitial, Case ***grille, int taille)
 *\brief Constructeur d'une composante connexe. Permet de créer une composante connexe à partir d'une case et de la grille. Ne crée pas la liste des voisins de la composante connexe.
 *		Voir aussi voisinsConnexes().
 *\param emplacementInitial Pointeur vers la case à partir de laquelle on veut créer une composante connexe.
 *\param grille Pointeur vers la grille de jeu. La grille doit-être non NULL.
 *\param taille Taille de la grille de jeu.
 *\return ComposanteConnexe initialisée avec ses cases et sa couleur, mais pas ses composantes connexes voisines.
 */
ComposanteConnexe constructeurComposanteConnexe(Case *emplacementInitial, Case **grille, int taille);

/**\fn ComposanteConnexe * creeComposanteConnexe(Case *emplacementInitial, Case ***grille, int taille)
 *\brief Fonction retournant un ponteur vers une composante connexe qu'il crée. Permet de créer une composante connexe à partir d'une case et de la grille. Ne crée pas la liste des voisins de la composante connexe.
 *		Utililisé seulement pour les tests unitaires.
 *\param emplacementInitial Pointeur vers la case à partir de laquelle on veut créer une composante connexe.
 *\param grille Pointeur vers la grille de jeu. La grille doit-être non NULL.
 *\param taille Taille de la grille de jeu.
 *\return ComposanteConnexe initialisée avec ses cases et sa couleur, mais pas ses composantes connexes voisines.
 */
ComposanteConnexe * creeComposanteConnexe(Case * emplacementInitial, Case **grille, int taille); /*Juste pour les testsU*/

/**\fn void destructeurComposanteConnexe(ComposanteConnexe *cc)
 *\brief Destructeur d'une composante connexe, libère la mémoire.
 *\param cc Pointeur vers la composante connexe à détruire.
 *\return void
 */
void destructeurComposanteConnexe(ComposanteConnexe *cc);

/**\fn ListeCase getCasesComposanteConnexe(ComposanteConnexe *cc)
 *\brief Getter pour obtenir les cases qui composent la composante connexe.
 *\param cc pointeur vers La composante dont on veut la liste des cases qui la compose.
 *\return La liste des cases qui composent la composante connexe.
 */
ListeCase getCasesComposanteConnexe(ComposanteConnexe *cc);

/**\fn ListeComposanteConnexe getComposantesVoisinesComposanteConnexe(ComposanteConnexe *cc)
 *\brief Getter pour obtenir les voisins de la composante connexe.
 *\param cc pointeur vers la composante dont on veut la liste des voisins.
 *\return La liste des voisins la composante connexe.
 */
ListeComposanteConnexe getComposantesVoisinesComposanteConnexe(ComposanteConnexe *cc);

/**\fn Couleur getCouleurComposanteConnexe(ComposanteConnexe *cc)
 *\brief Getter pour obtenir la couleur de la composante connexe.
 *\param cc pointeur vers la composante dont on veut la couleur.
 *\return La couleur de la composante connexe.
 */
Couleur getCouleurComposanteConnexe(ComposanteConnexe *cc);

/**\fn void setCouleurComposanteConnexe(ComposanteConnexe *cc, Couleur c)
 *\brief Setter pour modifier la couleur de la composante connexe.
 *\param cc pointeur vers la composante dont on veut changer la couleur.
 *\param c couleur que l'on veut attrivuer à la composante connexe
 *\return void
 */
void setCouleurComposanteConnexe(ComposanteConnexe *cc, Couleur c);

/**\fn void setComposantesVoisinesComposanteConnexe(ComposanteConnexe *cc, ListeComposanteConnexe l)
 *\brief Setter pour modifier la liste des composantes connexes voisines de la composante connexe.
 *\param cc pointeur vers la composante dont on veut modifier la liste de voisins .
 *\param l liste de composantes connexes que l'on veut attrivuer aux voisins de la composante connexe cc
 *\return void
 */
void setComposantesVoisinesComposanteConnexe(ComposanteConnexe *cc, ListeComposanteConnexe l);

/**\fn void setCasesComposanteConnexe(ComposanteConnexe *cc,ListeCase lc)
 *\brief Setter pour modifier la liste des cases de la composante connexe.
 *\param cc pointeur vers la composante dont on veut modifier la liste des cases .
 *\param lc liste de cases que l'on veut attrivuer de la composante connexe cc
 *\return void
 */
void setCasesComposanteConnexe(ComposanteConnexe *cc,ListeCase lc);

/**\fn ListeCase voisinsConnexes(Case *depart, Case ***grille, int taille)
 *\brief Fonction pour obtenir la liste de toutes les cases voisines de même couleur d'une case passée en paramètre.
 *\param depart Pointeur vers la case dont ont veut toutes les cases voisines de même couleur.
 *\param grille Pointeur vers la grille de jeu, non NULL.
 *\param taille La taille de la grille de jeu.
 *\return La liste des cases voisines de la case depart de même couleur.
 */
ListeCase voisinsConnexes(Case *depart, Case **grille, int taille);

/**\fn int **tableauTestAppartenance(int taille)
 *\brief Fonction qui renvoie un tableau d'entier remplis de 0.
 *\param taille La taille du tableau.
 *\return Un pointeur vers le tableau 2D crée.
 */
int **tableauTestAppartenance(int taille);

/**\fn int **completeGrilleTest(ListeCase aCompleter, int **grilleTest)
 *\brief Fonction qui permet de mettre à jour les cases complétées dans un tableau 2D de test.
 *\param aCompleter La liste des cases que l'on a déjà complétées.
 *\param grilleTest Le tableau 2D de test que l'on veut compléter.
 *\return Le tableau de test complété.
 */
int **completeGrilleTest(ListeCase aCompleter, int **grilleTest);


/**\fn void destructeurTableauTest(int **tab, int taille)
 *\brief Destructeur du tableau 2D test, libère la mémoire allouée.
 *\param tab Tableau 2D d'entier à détruire.
 *\param taille La taille du tableau 2D à détruire.
 *\return void
 */
void destructeurTableauTest(int **tab, int taille);

/**\fn int estIdentique(ComposanteConnexe *cc1, ComposanteConnexe *cc2)
 *\brief Fonction de test pour savoir si 2 ComposantesConnexes sont identiques.
 *\param cc1 La première composante connexe à comparer.
 *\param cc2 La deuxième composante connexe à comparer.
 *\return Renvoie 0 si les composantes connexes sont différentes, 1 sinon.
 */
int estIdentique(ComposanteConnexe *cc1, ComposanteConnexe *cc2);

/**\fn int estVoisine(ComposanteConnexe *cc1, ComposanteConnexe *cc2)
 *\brief Une fonction vérifie si 2 composantes connexes sont voisines
 *\param cc1 la première composante connexe dont on veut vérifier si elle est vosine de deuxième
 *\param cc2 la deuxième composante connexe dont on veut vérifier si elle est vosine de le première
 *\return 1 si elles sont voisines, 0 sinon
 */
int estVoisine(ComposanteConnexe *cc1, ComposanteConnexe *cc2);

/**\fn ListeCase casesVoisines(ListeCase casesComposanteConnexe, Case **grille, int taille)
 *\brief Une fonction qui renvoie toutes les cases voisines d'une liste de cases donnée en argument.
 *\param casesComposanteConnexe La liste des cases dont on veut les voisins.
 *\param grille La grille qui contient toutes les cases du jeu.
 *\param taille La taille de la grille.
 *\return La liste des cases voisines à la liste de cases passées en paramètre.
 */
ListeCase casesVoisines(ListeCase casesComposanteConnexe, Case **grille, int taille);

/**\fn ListeCase supprimeCasesDansListe(ListeCase casesAEnlever, ListeCase listeATronquer)
 *\brief Suprime une liste de cases dans une autre liste de cases. L'ordre des cases dans les listes ne rentre pas en compte.
 *\param casesAEnlever La liste des cases à enlever.
 *\param listeATronquer La liste des cases à laquelle on enlève les cases.
 *\return La liste une fois les cases enlevées
 */
ListeCase supprimeCasesDansListe(ListeCase casesAEnlever, ListeCase listeATronquer);

/**\fn ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, Case **grille, int taille, TabComposanteConnexe tabCC)
 *\brief Fonction qui définie les composantes connexes voisines d'une liste de cases donnée en paramètre.
 *\param casesComposanteConnexe La liste des cases de la composante connexe dont on veut les voisins.
 *\param grille La grille de jeu contenant toutes les cases.
 *\param taille La taille de la grille.
 *\param TabComposanteConnexe La liste de toutes les composantes connexes de la grille.
 *\return La liste de toutes les composantes connexes voisines à la liste de cases passée en paramètre.
 */
ListeComposanteConnexe definieComposantesConnexesVoisines(ListeCase casesComposanteConnexe, Case **grille, int taille, TabComposanteConnexe tabCC);

/**\fn void changementCouleurCase(ComposanteConnexe *cc, Couleur couleur)
 *\brief Fonction qui change la couleur des cases de la composante connexe entrée en paramètre
 *\param cc pointeur vers la composante connexe dont on veut changer la couleur des cases
 *\param couleur la couleur que l'on veut attribuer aux cases
 *\return void
 */
void changementCouleurCase(ComposanteConnexe *cc, Couleur couleur);

/**\fn ComposanteConnexe *changementCouleur(ComposanteConnexe *ccInitiale, TabComposanteConnexe *toutesComposantesConnexes, Couleur nouvelleCouleur)
 *\brief Fonction qui permet le changement de couleur d'une composante connexe. Met à jour les cases et les composantes connexes voisines de la composante connexe.
 *\param ccInitiale pointeur vers La composante connexe dont on veut changer le couleur.
 *\param touteComposantesConnexes Un pointeur vers la liste de toutes les composantes connexes.
 *\param nouvelleCouleur La nouvelle couleur de ccInitiale
 *\return Renvoie la composante connexe avec la nouvelle couleur et ses cases et composantes connexes voisines mis à jour.
 */
ComposanteConnexe *changementCouleur(ComposanteConnexe *ccInitiale, TabComposanteConnexe *toutesComposantesConnexes, Couleur nouvelleCouleur);

/*======================================================Tab composante connexe=============================================*/

/**\fn TabComposanteConnexe initTabComposanteConnexe()
 *\brief initialise un TabComposantConnexe à NULL.
 *\param void
 *\return NULL;
 */
TabComposanteConnexe initTabComposanteConnexe();

/**\fn int estVideTabComposanteConnexe(TabComposanteConnexe tabCC)
 *\brief Permet de savoir si un TabComposanteConnexe est NULL.
 *\param tabCC Le TabComposanteConnexe que l'on veut tester.
 *\return 0 si tabCC n'est pas NULL, 1 sinon.
 */
int estVideTabComposanteConnexe(TabComposanteConnexe tabCC);

/**\fn TabComposanteConnexe constructeurTabComposanteConnexe(ComposanteConnexe cc, TabComposanteConnexe tabCC)
 *\brief Constructeur d'un TabComposanteConnexe.
 *\param cc La composante connexe que l'on veut ajouter à la liste.
 *\param tabCC Le TabComposanteConnexe auquel on veut ajouter la composante connexe.
 *\return Un pointeur vers le TabComposanteConnexe nouvellement crée.
 */
TabComposanteConnexe constructeurTabComposanteConnexe(ComposanteConnexe cc, TabComposanteConnexe tabCC);

/**\fn TabComposanteConnexe constructeurTabComposanteConnexep(ComposanteConnexe *cc, TabComposanteConnexe tabCC)
 *\brief Constructeur d'un TabComposanteConnexe de pointeur.
 *\param cc pointeur de la composante connexe que l'on veut ajouter à la liste.
 *\param tabCC Le TabComposanteConnexe auquel on veut ajouter la composante connexe.
 *\return Un pointeur vers le TabComposanteConnexe nouvellement crée.
 */
TabComposanteConnexe constructeurTabComposanteConnexep(ComposanteConnexe *cc, TabComposanteConnexe tabCC);

/**\fn ComposanteConnexe * getValeurTabComposanteConnexe(TabComposanteConnexe tabCC)
 *\brief Permet d'obtenir un pointeur vers la tete d'un TabComposanteConnexe.
 *\param tabCC Le TabComposanteConnexe dont on veut la tete.
 *\return Un pointeur vers la tete du TabComposanteConnexe.
 */
ComposanteConnexe * getValeurTabComposanteConnexe(TabComposanteConnexe tabCC);

/**\fn TabComposanteConnexe getSuivantTabComposanteConnexe(TabComposanteConnexe tabCC)
 *\brief Permet d'obtenir la queue du TabComposanteConnexe.
 *\param tabCC Le TabComposanteConnexe dont on veut le suivant.
 *\return La queue de TabComposanteConnexe.
 */
TabComposanteConnexe getSuivantTabComposanteConnexe(TabComposanteConnexe tabCC);

/**\fn void destructeurCelluleTabComposanteConnexe(CelluleTabComposanteConnexe *cell)
 *\brief Destructeur d'une cellule de TabComposanteConnexe, libère la mémoire d'une cellule de TabComposanteConnexe et de la composante connexe qui le constitue.
 *\param cell Pointeur vers la cellule de TabComposanteConnexe que l'on veut libérer.
 *\return void
 */
void destructeurCelluleTabComposanteConnexe(CelluleTabComposanteConnexe *cell);

/**\fn void destructeurTabComposanteConnexe(TabComposanteConnexe tabCC)
 *\brief Destructeur de TabComposanteConnexe. Libère la mémoire d'une TabComposanteConnexe et de tous ces composants. Fait appel à destructeurCelluleTabComposanteConnexe.
 *\param tabCC Le TabComposanteConnexe que l'on veut détruire.
 *\return void
 */
void destructeurTabComposanteConnexe(TabComposanteConnexe tabCC);

/**\fn TabComposanteConnexe listeComposanteConnexeGrille(Case **grille, int tailleGrille)
 *\brief Fonction qui permet de construire toutes les composantes connexes d'une grille et de les stocker dans un TabComposanteConnexe.
 *\param grille La grille à partir de laquelle on veut créer le TabComposanteConnexe.
 *\param tailleGrille La taille de la grille.
 *\return Le TabComposanteConnexe avec toutes les composantes connexes crées dedans.
 */
TabComposanteConnexe listeComposanteConnexeGrille(Case **grille, int tailleGrille);

/**\fn TabComposanteConnexe creeVoisins(TabComposanteConnexe tabCC, Case **grille, int taille)
 *\brief Crée la liste des voisins de chacune des composantes connexes d'un TabComposanteConnexe
 *\param tabCC Le TabComposanteConnexe à qui l'on veut créer les voisins  pour chacune des composantes connexes.
 *\param grille La grille de jeu.
 *\param taille La taille de la grille de jeu.
 *\return la TabComposanteConnexe avec ses voisins créés
 */
TabComposanteConnexe creeVoisins(TabComposanteConnexe tabCC, Case **grille, int taille);

/**\fn int testVictoire(TabComposanteConnexe tabCC, ComposanteConnexe *cc)
 *\brief Fonction qui test savoir si il n'y a plus qu'une seule composante connexe.
 *\param taCC Le TabComposanteConnexe qui contient toutes les composantes connexes.
 *\param cc pointeur vers une composante connexe pour vérifier si elle a des voisins (si non elle est la seule composante connexe)
 *\return 0 si il y a plus d'une composante connexe, 1 sinon.
 */
int testVictoire(TabComposanteConnexe tabCC, ComposanteConnexe *cc);

/**\fn int longueurTabComposanteConnexe(TabComposanteConnexe tabCC)
 *\brief Fonction pour calculer la longueur d'un TabComposanteConnexe.
 *\param tabCC Le TabComposanteConnexe dont on veut la longueur.
 *\return La longueur du TabComposanteConnexe.
 */
int longueurTabComposanteConnexe(TabComposanteConnexe tabCC);

/**\fn TabComposanteConnexe supprimeElementTabComposanteConnexe(TabComposanteConnexe *tabCC)
 *\brief Supprime les éléments null du TabComposanteConnexe.
 *\param tabCC Un pointeur vers un TabComposanteConnexe auquel on veut supprimer les éléments null.
 *\return TabComposanteConnexe avec les élèments null supprimés
 */
TabComposanteConnexe supprimeElementTabComposanteConnexe(TabComposanteConnexe tabCC);

/**\fn int estDansComposanteConnexe(Case *c, ComposanteConnexe cc)
 *\brief Permet de savoir si une case est dans la composante connexe.
 *\param c La case à tester.
 *\param cc La composante connexe dont on veut savoir si elle contient la case.
 *\return 0 si la cases n'est pas dedans, 1 sinon.
 */
int estDansComposanteConnexe(Case *c, ComposanteConnexe cc);

/**\fn ComposanteConnexe *rechercheElementTabComposanteConnexeAvecCase(Case *c, TabComposanteConnexe tabCC)
 *\brief Permet de rechercher une composante connexe dans un TabComposanteConnexe à partir d'une case qui la compose.
 *\param c pointeur vers la case dont on veut la composante connexe à laquelle elle appartient.
 *\param tabCC Le TabComposanteConnexe dans lequel on cherche la composante connexe.
 *\return Un pointeur vers la composante connexe dans le TabComposanteConnexe qui contient la case que l'on cherche.
 */
ComposanteConnexe *rechercheElementTabComposanteConnexeAvecCase(Case *c, TabComposanteConnexe tabCC);

/**\fn int estPresentElementTabComposanteConnexe(ComposanteConnexe *cc, TabComposanteConnexe tabCC)
 *\brief Vérifie si une composante connexe est présent dans une TabComposanteConnexe
 *\param cc pointeur vers la composante connexe que l'on cherche.
 *\param tabCC Le TabComposanteConnexe dans lequel on cherche la composante connexe.
 *\return 1 si la composante connexe est présente dans la TabComposanteConnexe, 0 sinon
 */
int estPresentElementTabComposanteConnexe(ComposanteConnexe *cc, TabComposanteConnexe tabCC);

/**\fn int rangTabComposanteConnexe(ComposanteConnexe *cc, TabComposanteConnexe tabCC)
 *\brief Détermine la position d'une composante connexe dans une TabComposanteConnexe
 *\param cc pointeur vers la composante connexe dont on cherche la position
 *\param tabCC Le TabComposanteConnexe dans lequel on cherche la composante connexe.
 *\return la position de la composante connexe si elle est présente, -1 si elle ne l'est pas
 */
int rangTabComposanteConnexe(ComposanteConnexe *cc, TabComposanteConnexe tabCC);

#endif
