#include "ComposanteConnexe.h"
#include "Grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "colorFlood.h"

#include "ListeComposanteConnexe.h"

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>


void test(){
	CU_ASSERT(testTaille(24)==1);
	CU_ASSERT(testTaille(28)==0);
	
