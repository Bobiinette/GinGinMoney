#include <stdio.h>
#include <stdlib.h>

void solveur(char chemin,TabComposanteConnexe tab, ComposanteConnexe *cc){
  File* fichier=NULL;
  int * taille_max=malloc(sizeof(int));

  fichier=fopen(chemin,"w+");
  if (fichier==NULL){
    perror("Erreur ouverture du fichier du solveur ");
    exit(EXIT_FAILURE);
  }

  taille_max=longueurTabComposanteConnexe(tab);

}
