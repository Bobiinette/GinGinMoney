
#include "ComposanteConnexe.h"
#include "Grille.h"
#include "ListeComposanteConnexe.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*void testCreationTabComposanteConnexe() {
	printf("\n");
	Case **grille;
	int taille = 6;
	ComposanteConnexe *cc;
	grille = remplissageFichier("./test", taille);
	TabComposanteConnexe tabCC = initTabComposanteConnexe();
	TabComposanteConnexe save = initTabComposanteConnexe();
	save = tabCC;
	int sommeCases = 0;
	int i = 0;
	int tabCases[17] =    {1,2,1,1,2,3,1,2,5,1,3,4,4,1,1,3,1};
	int tabCouleurs[17] = {2,1,5,5,2,3,1,3,4,2,0,5,3,4,1,2,0};
	int tabVoisins[17] =  {1,4,2,4,4,5,4,2,5,4,7,5,4,2,3,4,2};

	CU_ASSERT(estVideTabComposanteConnexe(tabCC));
	tabCC = listeComposanteConnexeGrille(grille, taille);
	save = tabCC;
	CU_ASSERT(!estVideTabComposanteConnexe(tabCC));
	CU_ASSERT(longueurTabComposanteConnexe(tabCC) == 17);

	while(!estVideTabComposanteConnexe(tabCC)) {
		CU_ASSERT(estVideListeComposanteConnexe(getComposantesVoisinesComposanteConnexe(getValeurTabComposanteConnexe(tabCC)))); /*Les vosins doivent tous être vides*/
		/*tabCC = getSuivantTabComposanteConnexe(tabCC);
	}

	tabCC = save;
	tabCC = creeVoisins(tabCC, grille, taille);

	while(!estVideTabComposanteConnexe(tabCC)) {
		sommeCases += longueurListeCase(getCasesComposanteConnexe(getValeurTabComposanteConnexe(tabCC)));
		CU_ASSERT(longueurListeCase(getCasesComposanteConnexe(getValeurTabComposanteConnexe(tabCC))) == tabCases[i]);
		CU_ASSERT(getCouleurComposanteConnexe(getValeurTabComposanteConnexe(tabCC)) == tabCouleurs[i]);
		CU_ASSERT(longueurListeComposanteConnexe(getComposantesVoisinesComposanteConnexe(getValeurTabComposanteConnexe(tabCC))) == tabVoisins[i]);
		tabCC = getSuivantTabComposanteConnexe(tabCC);
		i ++;
	}

	tabCC = save;

	cc = getValeurTabComposanteConnexe(tabCC);

	CU_ASSERT(longueurListeCase(getCasesComposanteConnexe(cc)) == 1);
	CU_ASSERT(getCouleurComposanteConnexe(cc) == R);
	cc = changementCouleur(cc, &tabCC, M);
	CU_ASSERT(longueurListeCase(getCasesComposanteConnexe(cc)) == 6);
	CU_ASSERT(getCouleurComposanteConnexe(cc) == M);

	CU_ASSERT(sommeCases == taille * taille);
	tabCC = save;
	i = 0;

	destructeurTabComposanteConnexe(save);
	liberationGrille(grille, taille);
}*/

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	/*CU_pSuite pSuite = NULL;
	CU_initialize_registry();
	pSuite = CU_add_suite("Suite", NULL, NULL);

	CU_add_test(pSuite,"test de testCreationTabComposanteConnexe()",testCreationTabComposanteConnexe);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();*/

	Case **grille;
	int taille = 6;
	ComposanteConnexe *cc;
	grille = remplissageFichier("./test", taille);
	TabComposanteConnexe tabCC = initTabComposanteConnexe();
	TabComposanteConnexe test = initTabComposanteConnexe();
	tabCC = listeComposanteConnexeGrille(grille, taille);
	cc = getValeurTabComposanteConnexe(tabCC);
	test = constructeurTabComposanteConnexep(cc, test);
	printf("%d\n", longueurTabComposanteConnexe(test));

	return 0;
}