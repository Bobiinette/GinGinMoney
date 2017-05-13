#include "Grille.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*Teste du module Grille.c*/

void testCreationCases(){ /*Test de la fonction tableauVide. Pour tester cette fonction on a besoin des fonctions getXCase, getXCase et getCaseGrille qui sont donc tester elles aussi*/
  Case **grille;
  int i,j;
  int taille=2;
  grille=tableauVide(2); /*initialisation d'un tableau de taille 2 sans couleur*/
  for (i=0; i<taille; i++){ /*vérification que chaque case du tableau a les bons cooredonnées*/
    for (j=0; j<taille; j++){
      printf("vérification du remplissage de la grille à la %d ligne et %d colonne\n",i,j);
      CU_ASSERT(getXCase(getCaseGrille(grille,i,j))==i);
      CU_ASSERT(getYCase(getCaseGrille(grille,i,j))==j);
    }
  }
  liberationGrille(grille,taille); /*libération de la mémoire*/
  grille = NULL;

  grille=tableauVide(-2);
  CU_ASSERT(grille==NULL);/*vérification qu'il ne se passe rien si on rentre un nombre négatif*/
}

void testRemplissageFichier(){ /*test de a fonction remplissageFichier. Pour tester cette fonction, on a besoin de la fonction getCouleurCase qui est également tester*/
  Case **grille;
  int taille=6;
  grille=remplissageFichier("./test",taille); /*remplie la grille avec le fichier test*/
  printf("test de la première ligne du tableau avec le fichier test");
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,0,0))==B);/*on teste pour chaque case de la première ligne si la couleur attribuée est la même que celle du fichier*/
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,0,1))==R);
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,0,2))==R);
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,0,3))==R);
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,0,4))==V);
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,0,5))==M);

  printf("test de la première colonne avec le fichier test");
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,1,0))==J);/*on teste pour chaque case de la première colonne si la couleur attribuée est la même que celle du fichier*/
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,2,0))==J);
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,3,0))==J);
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,4,0))==R);
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,5,0))==G);
  /*en testant le première ligne et la première colonne on a fait des tests avec toutes les couleurs qui peuvent exister dans la grille*/
  liberationGrille(grille,taille);/*libération de l'espace mémoire*/

}

void testSetCouleur(){/*Test la fonction setCouleur*/
  Case **grille;
  grille=tableauVide(2);/*création d'une grille de 2 cases sans couleur*/
  setCouleur(getCaseGrille(grille,0,0),J);/*je donne la couleur jaune à la case (0.0)*/
  CU_ASSERT(getCouleurCase(getCaseGrille(grille,0,0))==J);/*je vérifie que la case (0.0) a bien la couleur jaune*/
  liberationGrille(grille,2);/*libération de l'espace mémoire*/
}

 int main() {
  srand(time(NULL));
  CU_pSuite pSuite = NULL;
 	CU_initialize_registry();
 	pSuite = CU_add_suite("Suite", NULL, NULL);

  CU_add_test(pSuite,"test de testCreationCases()",testCreationCases);
  CU_add_test(pSuite,"test de testRemplissageFichier()",testRemplissageFichier);
  CU_add_test(pSuite,"test de testSetCouleur()",testSetCouleur);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
  return 0;
}
