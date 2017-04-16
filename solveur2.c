#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "solveur2.h"
#include <stdbool.h>

void solveur(char *chemin,TabComposanteConnexe tab, Case **grille){
  const int taille = longueurTabComposanteConnexe(tab);
	char str[taille + 1];
  FILE *fichier=NULL;
  int * taille_max=malloc(sizeof(int));
  int longueurCompoConnexe = longueurTabComposanteConnexe(tab);
  printf("salut");
  fichier=fopen(chemin,"w+");
  if (fichier==NULL){
    perror("Erreur ouverture du fichier du solveur ");
    exit(EXIT_FAILURE);
  }
  taille_max=&longueurCompoConnexe;
  solveurDeuxRecursif(&tab,fichier, 0, taille_max, grille, str);
  fclose(fichier);
}

ComposanteConnexe *changementCouleurComposanteConnexe(ComposanteConnexe *ccInitiale, TabComposanteConnexe *toutesComposantesConnexes, Couleur nouvelleCouleur) {
	if(ccInitiale == NULL) {
		printf("Impossible de changer la couleur de NULL");
		return NULL;
	}
	else if(getCouleurComposanteConnexe(ccInitiale) == nouvelleCouleur) {
		printf("Impossible de changer la couleur, la couleur est la même qu'à l'origine\n");
		return ccInitiale;
	}
	ListeComposanteConnexe aParcourir = getComposantesVoisinesComposanteConnexe(ccInitiale);
	setCouleurComposanteConnexe(ccInitiale, nouvelleCouleur);
	ComposanteConnexe *tmp = NULL;
	ComposanteConnexe *tmp2 = NULL; /*juste pour stocker getValeurListeComposanteConnexe(tmp->listeVoisins) et améliorer la lisibilité*/
	ListeComposanteConnexe voisinsBonneCouleur = initListeComposanteConnexe();
	ListeComposanteConnexe save = initListeComposanteConnexe();
	ListeComposanteConnexe voisinsEltSelectionne = initListeComposanteConnexe();
	ListeComposanteConnexe nouveauxVoisins = initListeComposanteConnexe();

	/*D'abord on regarde les omposantes connexes voisines de la bonne couleur*/
	while(!estVideListeComposanteConnexe(aParcourir)) {
		tmp = getValeurListeComposanteConnexe(aParcourir);
		if(getCouleurComposanteConnexe(tmp) == nouvelleCouleur) {
			setCasesComposanteConnexe(ccInitiale, concatenationListeCase(getCasesComposanteConnexe(ccInitiale), getCasesComposanteConnexe(tmp)));
			setCasesComposanteConnexe(tmp, NULL);
			voisinsBonneCouleur = constructeurListeComposanteConnexe(voisinsBonneCouleur, tmp);

			setCouleurComposanteConnexe(tmp, H);
		}
		/*Si la composante connexe n'est pas de la bonne couleur, on la remet dans les voisins*/
		else if(getCouleurComposanteConnexe(tmp) != H) {
			nouveauxVoisins = constructeurListeComposanteConnexe(nouveauxVoisins, tmp);
		}
		aParcourir = getSuivantListeComposanteConnexe(aParcourir);
		tmp = NULL;
	}
	save = voisinsBonneCouleur;

	/*Puis on ajoute les voisins des composantes connexes voisines de la bonne couleur aux voisins de ccInitiale*/
	while(!estVideListeComposanteConnexe(voisinsBonneCouleur)) {
		voisinsEltSelectionne = getComposantesVoisinesComposanteConnexe(getValeurListeComposanteConnexe(voisinsBonneCouleur));

		while(!estVideListeComposanteConnexe(voisinsEltSelectionne)) {
			tmp2 = getValeurListeComposanteConnexe(voisinsEltSelectionne);

			if(!estPresentElementTabComposanteConnexe(tmp2, *toutesComposantesConnexes)) {
				tmp2 = NULL;
			}

			if(tmp2 != NULL) {
				if(getCouleurComposanteConnexe(tmp2) != H) {
					if(getCouleurComposanteConnexe(tmp2) != nouvelleCouleur && !rechercheElementListeComposanteConnexe(nouveauxVoisins, tmp2)) {
						nouveauxVoisins = constructeurListeComposanteConnexe(nouveauxVoisins, tmp2);
					}
				}
			}
			voisinsEltSelectionne = getSuivantListeComposanteConnexe(voisinsEltSelectionne);
		}
		voisinsBonneCouleur = getSuivantListeComposanteConnexe(voisinsBonneCouleur);
	}
	destructeurListeComposanteConnexe(save);
	save = NULL;
	destructeurListeComposanteConnexe(getComposantesVoisinesComposanteConnexe(ccInitiale));
	setComposantesVoisinesComposanteConnexe(ccInitiale, NULL);
	*toutesComposantesConnexes = supprimeElementTabComposanteConnexe(*toutesComposantesConnexes);
	setComposantesVoisinesComposanteConnexe(ccInitiale, nouveauxVoisins);
	return ccInitiale;
}

TabComposanteConnexe copieTabCompoConnexe(TabComposanteConnexe tab){
  TabComposanteConnexe res;
  ComposanteConnexe *t;
  res=initTabComposanteConnexe();
  while(!estVideTabComposanteConnexe(tab)){
    t=getValeurTabComposanteConnexe(tab);
    res=constructeurTabComposanteConnexep(t, res);
    tab=getSuivantTabComposanteConnexe(tab);
  }
  return res;
}

bool couleurPresenteVoisin(TabComposanteConnexe *tab, Couleur c, Case **grille){
  ListeComposanteConnexe *listeVoisins;
  ComposanteConnexe *composantePrincipale;
  ComposanteConnexe *ccVoisin;
  composantePrincipale=rechercheElementTabComposanteConnexeAvecCase(getCaseGrille(grille,0,0), *tab);
  *listeVoisins=getComposantesVoisinesComposanteConnexe(composantePrincipale);
  while(!estVideListeComposanteConnexe(*listeVoisins)){
    ccVoisin = getValeurListeComposanteConnexe(*listeVoisins);
    if (getCouleurComposanteConnexe(ccVoisin) == c){
      return true;
    }
    *listeVoisins=getSuivantListeComposanteConnexe(*listeVoisins);
  }
  return false;
}

void solveurDeuxRecursif(TabComposanteConnexe *tab, FILE *f, int nbrCoups, int *nbrCoupsMax, Case **grille, char *test){
  ComposanteConnexe *composantePrincipale;
  composantePrincipale=rechercheElementTabComposanteConnexeAvecCase(getCaseGrille(grille,0,0), *tab);
  if (nbrCoups > *nbrCoupsMax){
    fputc('H',f);
    fputc('\n',f);
  }
  if (testVictoire(*tab, composantePrincipale)){
    nbrCoupsMax = &nbrCoups;
    fputs(test,f);
    fputc('\n',f);
  }
  else{
    int i;
    for (i=1; i<7; i++){
      if (couleurPresenteVoisin(tab,i,grille)){
        *tab = copieTabCompoConnexe(* tab);
        composantePrincipale=rechercheElementTabComposanteConnexeAvecCase(getCaseGrille(grille,0,0), *tab);
        test[nbrCoups]=conversionEntierChar(i);
        test[nbrCoups + 1] = '\0';
        changementCouleurComposanteConnexe(composantePrincipale, tab, i);
        solveurDeuxRecursif(tab,f, nbrCoups + 1, nbrCoupsMax, grille,test);
      }
    }
  }

}
