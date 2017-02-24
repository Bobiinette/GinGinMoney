
#include "ComposanteConnexe.h"
#include "Grille.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void testCreationTabComposanteConnexe() {
	printf("\n");
	Case **grille;
	int taille = 6;
	grille = remplissageFichier("./test", taille);

	TabComposanteConnexe tabCC = initTabComposanteConnexe();
	CU_ASSERT(estVideTabComposanteConnexe(tabCC));
	tabCC = listeComposanteConnexeGrille(grille, taille);
	CU_ASSERT(!estVideTabComposanteConnexe(tabCC));

	printf("Fini\n");
	printf("Nombre de composantes connexes : %d", longueurTabComposanteConnexe(tabCC));

	destructeurTabComposanteConnexe(tabCC);
	liberationGrille(grille, taille);
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	CU_pSuite pSuite = NULL;
	CU_initialize_registry();
	pSuite = CU_add_suite("Suite", NULL, NULL);

	CU_add_test(pSuite,"test de testCreationTabComposanteConnexe()",testCreationTabComposanteConnexe);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return 0;
}