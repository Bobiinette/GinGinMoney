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

int getXCase(Case test){
  return test.x;
}

int getYCase(Case test){
  return test.y;
}

int getCouleurCase(Case test){
  return test.couleur;
}

void setCouleur(Case * test, Couleur c){
  test->couleur=c;
}

Case ** tableauVide(int n){
  int i;
  Case ** res=calloc(n,sizeof(Case *));

  for (i=0;i<n;i++)
    res[i]=calloc(n,sizeof(Case));

  return res;
}


/*void liberationGrille(Case ** tab){
  int i;

  int len=sizeof(tab);
  for (i=0;i<
  free(tab);
}*/


/*Fonction de remplissage aléatoire du tableau*/
static Couleur aleatoire(){
  Couleur res;

  res=random()%6;
  return res;
}


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


/*Fonction de remplissage du tableau à partir d'un fichier*/
static void erreurOuverture(int check){
  if (check){
    perror("Erreur ouverture du fichier.\n");
    exit(EXIT_FAILURE);
  }
}

static void erreurLecture(int check){
  if (check){
    perror("Erreur lecture du fichier.\n");
    exit(EXIT_FAILURE);
  }
}


/*Le fichier contient des chaines de caractères contenant un retour à la ligne au bout de chaque ligne*/
Couleur ** remplissageFichier(FILE * text){
  FILE * fichier=NULL;
  int lecture;  /*lecture caractère par caractère dans le fichier*/
  char buff;
  int k=0; /*variable permettant de déterminer la longueur de la première ligne et de déduire la taille*/
  int taille;  /*taille de la grille*/
  int i,j;
  Couleur ** res;

  fichier=fopen(text,O_RDONLY);
  erreurOuverture(fichier==NULL);

  do{  /*remplissage de la première ligne*/
    lecture=read(fichier,&buff,sizeof(buff));
    erreurLecture(lecture<0);
    res[0][k]=buff;  /*remplissage de la première ligne*/
    k++;  /*à la fin de la boucle, i sera la taille de la grille*/
  } while (buff!="\n");
  
  taille=k;

  for (i=1;i<taille;i++){ /*remplissage du reste du tableau*/
    for (j=0;j<taille;j++){ 
      lecture=read(fichier,&buff,sizeof(buff));
      erreurLecture(lecture<0);
      res[i][j]=buff;
    }
  }  /*traiter le cas "/n" à la fin de la ligne*/

  return res;
}



