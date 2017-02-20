#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Grille.h"

struct Case{
  int x;
  int y;
  Couleur couleur;
};

/*@requires Récupère l'abscisse de la case considérée*/
int getXCase(Case *test){
  return test->x;
}

/*@requires Récupère l'ordonnée de la case considérée*/
int getYCase(Case *test){
  return test->y;
}

/*@requires Récupère la couleur de la case considérée*/
int getCouleurCase(Case *test){
  return test->couleur;
}

/*@requires Change la couleur de la case considérée par la couleur en paramètre*/
void setCouleur(Case * test, Couleur c){
  test->couleur=c;
}

/*@requires Initialise un tableau vide de taille n*/
Case ** tableauVide(int n){
  int i;
  Case ** res=calloc(n,sizeof(Case *));

  for (i=0;i<n;i++)
    res[i]=calloc(n,sizeof(Case));

  return res;
}


/*@requires Libère l'espace mémoire occupé par la grille*/
void liberationGrille(Case ** tab, int taille){
  int i;

  for (i=0;i<taille;i++){
      free(tab[i]);
  }
  free(tab);
}


/*@requires Renvoie une couleur aléatoirement*/
static Couleur aleatoire(){
  Couleur res;

  res=random()%6;
  return res;
}

/*@requires Fonction de remplissage aléatoire du tableau*/
Case ** remplissageAleatoire(int n, Case **tab){
  int i,j;

  for (i=0;i<n;i++){
    for (j=0;j<n;j++){
      (tab[i][j]).couleur = aleatoire();
    }
  }
  return tab;
}


/*@requires Fonction de remplissage du tableau à partir d'un fichier*/
static void erreurOuverture(int check){
  if (check){
    perror("Erreur ouverture du fichier.\n");
    exit(EXIT_FAILURE);
  }
}


/*@requires Vérifie la longueur des chaines de caractères dans le fichier*/
static void erreurLongueur(int check){
  if (check){
    perror("Erreur longueur de la chaîne de caractères dans le fichier.\n");
    exit(EXIT_FAILURE);
  }
}


/*@requires Vérifie qu'on n'est pas à la fin du fichier*/
static void erreurFinFichier(int check){
  if (check){
    perror("Erreur fin du fichier : tableau non remplie.\n");
    exit(EXIT_FAILURE);
  }
}


/*@requires Vérifie que la couleur existe*/
static void checkCouleur(char buff){
  int check;  /*1 si buff est bien une couleur, 0 sinon*/

  check = (buff==B || buff==V || buff==R);
  check = (check || buff==J || buff==M || buff==G);

  if (!check){
    perror("Erreur couleur inexistante.\n");
    exit(EXIT_FAILURE);
  }
}


/*@requires Le fichier contient des chaines de caractères contenant un retour à la ligne au bout de chaque ligne
  @ensures Crée un tableau de couleur à partir d'un fichier*/
Couleur ** remplissageFichier(char * text){
  FILE * fichier=NULL;
  int lecture;  /*lecture caractère par caractère dans le fichier*/
  char buff;
  int k=0; /*variable permettant de déterminer la longueur de la première ligne et d'en déduire la taille*/
  int taille;  /*taille de la grille*/
  int i,j;
  Couleur ** res;

  fichier=fopen(text,"r");
  erreurOuverture(fichier==NULL);

  do{  /*remplissage de la première ligne*/
    buff=fgetc(fichier);
    checkCouleur(buff); /*vérifie si la couleur existe*/
    if (buff!='\n')
      res[0][k]=buff;  /*remplissage de la première ligne*/
    k++;  /*à la fin de la boucle, k sera la taille de la grille*/
  } while (buff!='\n');
  
  taille=k;

  for (i=1;i<taille;i++){ /*remplissage du reste du tableau*/
    for (j=0;j<taille;j++){ 
      buff=fgetc(fichier);
      erreurLongueur(buff=='\n');  /*vérifie la longueur de la chaine de caractères en cours de lecture*/
      erreurFinFichier(buff==EOF); /*vérifie qu'on n'est pas à la fin du fichier*/
      checkCouleur(buff);  /*vérifie si la couleur existe*/
      res[i][j]=buff;
    }
    fgetc(fichier);  /*lit le caractère "\n" après chaque fin de ligne*/
  }

  fclose(fichier);
  return res;
}

