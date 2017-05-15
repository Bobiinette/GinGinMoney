#include "ListeComposanteConnexe.h"
#include "ComposanteConnexe.h"
#include "Grille.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include <stdio.h>

void testCreationListeComposanteConnexe(){
  /*code*/
  int taille=6;
  Case **grille = remplissageFichier("./test",taille);
  ListeComposanteConnexe l;
  ComposanteConnexe *c = creeComposanteConnexe(getCaseGrille(grille,0,0),grille,taille);
  ComposanteConnexe *d = creeComposanteConnexe(getCaseGrille(grille,0,1),grille,taille);
  l=initListeComposanteConnexe();
  CU_ASSERT(estVideListeComposanteConnexe(l)); /*on teste ici si la liste créée est bien vide*/
  l = constructeurListeComposanteConnexe(l, c);
  CU_ASSERT(!estVideListeComposanteConnexe(l)); /*on teste si la liste n'est plus vide après avoir ajoutée une composante connexe dedans*/
  l = constructeurListeComposanteConnexe(l, d);
  CU_ASSERT(getValeurListeComposanteConnexe(l)==d); /*on regarde si la tête de la liste est bien celle du constructeur*/
  CU_ASSERT(getValeurListeComposanteConnexe(getSuivantListeComposanteConnexe(l))==c); /*on vérifie si le suivant du premier élément de la liste est bien celui donné*/
  CU_ASSERT(longueurListeComposanteConnexe(l)==2); /*on teste si la longueur de la liste est exacte après l'ajout des deux éléments dans la liste */

  destructeurListeComposanteConnexe(l);
  destructeurComposanteConnexe(c);
  destructeurComposanteConnexe(d);
  free(c);
  free(d);
  liberationGrille(grille, taille);
}

void testFonctionsDiversesListeComposanteConnexe(){
  int taille=6;
  Case **grille = remplissageFichier("./test",taille);
  ListeComposanteConnexe l;
  ComposanteConnexe *re = creeComposanteConnexe(getCaseGrille(grille,0,0),grille,taille);
  ComposanteConnexe *cc = creeComposanteConnexe(getCaseGrille(grille,0,5),grille,taille);
  ComposanteConnexe *d = creeComposanteConnexe(getCaseGrille(grille,5,0),grille,taille);
  ComposanteConnexe *e = creeComposanteConnexe(getCaseGrille(grille,1,1),grille,taille);
  ComposanteConnexe *f = creeComposanteConnexe(getCaseGrille(grille,1,4),grille,taille);
  l = initListeComposanteConnexe();
  l = constructeurListeComposanteConnexe(l, re);
  l = constructeurListeComposanteConnexe(l, cc);
  l = constructeurListeComposanteConnexe(l, d);
  l = constructeurListeComposanteConnexe(l, e);
  CU_ASSERT(longueurListeComposanteConnexe(l)==4); /*on teste la longueur de la liste*/
  /*CU_ASSERT(res!=NULL);*/ /*on vérifie si la composante connexe cc qui est dans la liste est bien trouvée par la fonction*/
  /*res = rechercheElementListeComposanteConnexe(l,f);*/
  /*CU_ASSERT(res==NULL);*/ /*on vérifie que la composante connexe f ne se trouvant pas dans la liste n'est pas trouvée par la fonction et renvoie bien NULL*/
  supprimeElementListeComposanteConnexe(l, e);
  CU_ASSERT(longueurListeComposanteConnexe(l)==3); /*une composante connexe ayant été supprimée, on regarde si la longueur de la liste a été soustraite de 1*/
  /*res = rechercheElementListeComposanteConnexe(l,copy);*/
  /*CU_ASSERT(res==NULL);*/ /*on regarde si la composante connexe supprimée n'est pas trouvée par la fonction de recherche afin de vérifier si l'élément supprimé est bien celui choisi par la fonction*/
  supprimeElementListeComposanteConnexe(l, f);
  CU_ASSERT(longueurListeComposanteConnexe(l)==3); /*on regarde si lorsqu'on veut supprimer un élément qui n'est pas dans la liste, celle-ci ne bouge pas, c'est-à-dire que la longueur de la liste est restée inchangée*/

  destructeurListeComposanteConnexe(l);
  destructeurComposanteConnexe(cc);
  destructeurComposanteConnexe(d);
  destructeurComposanteConnexe(e);
  destructeurComposanteConnexe(f);
  destructeurComposanteConnexe(re);
  free(cc);
  free(re);
  free(d);
  free(e);
  free(f);
  liberationGrille(grille, taille);
}

int main() {
  /* code */
  CU_pSuite pSuite = NULL;
	CU_initialize_registry();
	pSuite = CU_add_suite("Suite", NULL, NULL);

  CU_add_test(pSuite,"test de testCreationListeComposanteConnexe()",testCreationListeComposanteConnexe);
  CU_add_test(pSuite,"test de testFonctionsDiversesListeComposanteConnexe()",testFonctionsDiversesListeComposanteConnexe);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return 0;
}
