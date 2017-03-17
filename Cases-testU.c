#include "Cases.h"
#include "Grille.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include <stdio.h>

void testListe1(){
  /*Vérification liste vide*/
  ListeCase l=initListeCase();
  CU_ASSERT(testListeCaseVide(l));

  /*Création d'une case*/
  Case * c;
  c=constructeurCase(2,3,B);

  /*Création d'une autre case*/
  Case * c2;
  c2=constructeurCase(4,5,R);
  
  /*Remplissage de la liste de cases*/
  l=constructeurListeCase(c,l);  /*attention, si erreur, problème dans la partie 'Rajout'*/
  CU_ASSERT(!testListeCaseVide(l));

  /*Vérification récupération de la case*/
  Case * testCase=getValeurListeCase(l);
  CU_ASSERT(testCase==c);
  ListeCase testListe=getSuivantListeCase(l);
  CU_ASSERT(testListeCaseVide(testListe));

  /*Rajout et vérification que 'suivant' est cette fois-ci liste non vide*/
  l=constructeurListeCase(c2,l);
  ListeCase testListe2=getSuivantListeCase(l);
  CU_ASSERT(!testListeCaseVide(testListe2));

  destructeurListeCase(l);
  free(c);
  free(c2);
}

int verificationEgaliteListe(ListeCase l1,ListeCase l2){
  Case * case1;
  Case * case2;

  int res=1;
  while (!testListeCaseVide(l1) && !testListeCaseVide(l2)){
    case1=getValeurListeCase(l1);
    case2=getValeurListeCase(l2);
    if (case1!=case2){
      res=0;
      return res;
    }
    else{
      l1=getSuivantListeCase(l1);
      l2=getSuivantListeCase(l2);
    }
  }

  /*les deux prochaines conditions vérifient le cas où les deux listes sont de longueur différente*/
  if (!testListeCaseVide(l1))
    res=0;

  if (!testListeCaseVide(l2))
    res=0;
  
  return res;  
}

void testListe2(){
  ListeCase l=initListeCase();

  /*Création d'une case*/
  Case * c;
  c=constructeurCase(2,3,B);

  /*Création d'une autre case*/
  Case * c2;
  c2=constructeurCase(4,5,R);

  /*Création d'une autre case*/
  Case * c3;
  c3=constructeurCase(6,7,J);
  
  /*Remplissage de la liste de cases*/
  l=constructeurListeCase(c,l);
  l=constructeurListeCase(c2,l);
  CU_ASSERT(estPresentDansListeCase(c,l));
  CU_ASSERT(!estPresentDansListeCase(c3,l));

  /*Concaténation de deux listes*/
  ListeCase l2=initListeCase();
  l2=constructeurListeCase(c3,l2);
  ListeCase verif=initListeCase();
  verif=constructeurListeCase(c,verif);
  verif=constructeurListeCase(c2,verif);
  verif=constructeurListeCase(c3,verif);
  CU_ASSERT(verificationEgaliteListe(concatenationListeCase(l2,l),verif));/*La liste l2 vaut à présent l2 + l, la liste l a été absorbée par la concaténation*/

  /*Suppression d'un élément de la liste verif*/
  supprimeElementListeCase(c2,verif);
  ListeCase verif2=initListeCase();
  verif2=constructeurListeCase(c,verif2);
  verif2=constructeurListeCase(c3,verif2);
  CU_ASSERT(verificationEgaliteListe(verif2,verif));

  destructeurListeCase(l2);
  destructeurListeCase(verif);
  destructeurListeCase(verif2);
  free(c);
  free(c3);
  free(c2);
}


int main() {
	CU_pSuite pSuite = NULL;
	CU_initialize_registry();
	pSuite = CU_add_suite("Suite", NULL, NULL);

	CU_add_test(pSuite,"test de testListe1",testListe1);
	CU_add_test(pSuite,"test de testListe2",testListe2);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return 0;
}

