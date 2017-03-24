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

ComposanteConnexe *changementCouleurComposanteConnexe(ComposanteConnexe *ccInitiale, TabComposanteConnexe *toutesComposantesConnexes, Couleur nouvelleCouleur) {
	if(ccInitiale == NULL) {
		printf("Impossible de changer la couleur de NULL");
		return NULL;
	}
	else if(ccInitiale->couleur == nouvelleCouleur) {
		printf("Impossible de changer la couleur, la couleur est la même qu'à l'origine\n");
		return ccInitiale;
	}
	ListeComposanteConnexe aParcourir = ccInitiale->listeVoisins;
	ccInitiale->couleur = nouvelleCouleur;
	ComposanteConnexe *tmp = NULL;
	ComposanteConnexe *tmp2 = NULL; /*juste pour stocker getValeurListeComposanteConnexe(tmp->listeVoisins) et améliorer la lisibilité*/
	ListeComposanteConnexe voisinsBonneCouleur = initListeComposanteConnexe();
	ListeComposanteConnexe save = initListeComposanteConnexe();
	ListeComposanteConnexe voisinsEltSelectionne = initListeComposanteConnexe();
	ListeComposanteConnexe nouveauxVoisins = initListeComposanteConnexe();

	/*D'abord on regarde les omposantes connexes voisines de la bonne couleur*/
	while(!estVideListeComposanteConnexe(aParcourir)) {
		tmp = getValeurListeComposanteConnexe(aParcourir);
		if(tmp->couleur == nouvelleCouleur) {
			ccInitiale->cases = concatenationListeCase(ccInitiale->cases, tmp->cases);
			tmp->cases = NULL;
			voisinsBonneCouleur = constructeurListeComposanteConnexe(voisinsBonneCouleur, tmp);

			tmp->couleur = H;
		}
		/*Si la composante connexe n'est pas de la bonne couleur, on la remet dans les voisins*/
		else if(tmp->couleur != H) {
			nouveauxVoisins = constructeurListeComposanteConnexe(nouveauxVoisins, tmp);
		}
		aParcourir = getSuivantListeComposanteConnexe(aParcourir);
		tmp = NULL;
	}
	save = voisinsBonneCouleur;

	/*Puis on ajoute les voisins des composantes connexes voisines de la bonne couleur aux voisins de ccInitiale*/
	while(!estVideListeComposanteConnexe(voisinsBonneCouleur)) {
		voisinsEltSelectionne = getValeurListeComposanteConnexe(voisinsBonneCouleur)->listeVoisins;

		while(!estVideListeComposanteConnexe(voisinsEltSelectionne)) {
			tmp2 = getValeurListeComposanteConnexe(voisinsEltSelectionne);

			if(!estPresentElementTabComposanteConnexe(tmp2, *toutesComposantesConnexes)) {
				tmp2 = NULL;
			}

			if(tmp2 != NULL) {
				if(tmp2->couleur != H) {
					if(tmp2->couleur != nouvelleCouleur && !rechercheElementListeComposanteConnexe(nouveauxVoisins, tmp2)) {
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
	destructeurListeComposanteConnexe(ccInitiale->listeVoisins);
	ccInitiale->listeVoisins = NULL;
	*toutesComposantesConnexes = supprimeElementTabComposanteConnexe(*toutesComposantesConnexes);
	ccInitiale->listeVoisins = nouveauxVoisins;
	return ccInitiale;
}

TabComposanteConnexe copieTabCompoConnexe(TabComposanteConnexe tab){
  TabComposanteConnexe res;
  ComposanteConnexe *t;
  res=initTabComposanteConnexe();
  while(estVideTabComposanteConnexe(tab)){
    t=getValeurTabComposanteConnexe(tab);
    res=constructeurTabComposanteConnexe(t, res);
    tab=getSuivantTabComposanteConnexe(tab);
  }
  return res;
}
