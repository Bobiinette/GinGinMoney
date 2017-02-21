#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cunit.h>

enum Couleur {B,V,R,J,M,G};


struct t_case{
  int x;
  int y;
  Couleur couleur;
};

/**\brief Récupère l'abscisse de la case considérée**/
int getXCase(Case test){
  return test.x;
}

/**\brief Récupère l'ordonnée de la case considérée**/
int getYCase(Case test){
  return test.y;
}

/**\brief Récupère la couleur de la case considérée**/
int getCouleurCase(Case test){
  return test.couleur;
}

/**\brief Change la couleur de la case considérée par la couleur en paramètre**/
void setCouleur(Case * test, Couleur c){
  test->couleur=c;
}

/**\brief Initialise un tableau vide de taille n**/
Case ** tableauVide(int n){
  int i;
  Case ** res=calloc(n,sizeof(Case *));

  for (i=0;i<n;i++)
    res[i]=calloc(n,sizeof(Case));

  return res;
}


/**\brief Libère l'espace mémoire occupé par la grille**/
void liberationGrille(Case ** tab, int taille){
  int i,j;

  for (i=0;i<taille;i++){
    for (j=0;j<taille;j++)
      free(tab[i][j]);
  }
}


/**\brief Renvoie une couleur aléatoirement**/
static Couleur aleatoire(){
  Couleur res;

  res=random()%6;
  return res;
}

/**\brief Fonction de remplissage aléatoire du tableau**/
Couleur ** remplissageAleatoire(int n){
  Couleur ** res=tableauVide(n);
  int i,j;

  for (i=0;i<n;i++){
    for (j=0;j<n;j++){
      res[i][j]=aleatoire();
    }
  }
  return res;
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
  int check;  /*1 si buff est bien une couleur, 0 sinon*/

  check = (buff==B || buff==V || buff==R);
  check = (check || buff==J || buff==M || buff==G);

  if (!check){
    perror("Erreur couleur inexistante.\n");
    exit(EXIT_FAILURE);
  }
}


/**\brief Crée un tableau de couleur à partir d'un fichier. Le fichier doit contenir des chaines de caractères contenant un retour à la ligne au bout de chaque ligne**/
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
    if (buff!="\n")
      res[0][k]=buff;  /*remplissage de la première ligne*/
    k++;  /*à la fin de la boucle, k sera la taille de la grille*/
  } while (buff!="\n");
  
  taille=k;

  for (i=1;i<taille;i++){ /*remplissage du reste du tableau*/
    for (j=0;j<taille;j++){ 
      buff=fgetc(fichier);
      erreurLongueur(buff=="\n");  /*vérifie la longueur de la chaine de caractères en cours de lecture*/
      erreurFinFichier(buff==EOF); /*vérifie qu'on n'est pas à la fin du fichier*/
      checkCouleur(buff);  /*vérifie si la couleur existe*/
      res[i][j]=buff;
    }
    fgetc(fichier);  /*lit le caractère "\n" après chaque fin de ligne*/
  }

  fclose(fichier);
  return res;
}

