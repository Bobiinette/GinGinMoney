#include "ComposanteConnexe.h"
#include "Grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "colorFlood.h"
#include <termios.h>
#include "ListeComposanteConnexe.h"
#include "colorFlood_SDL.h"
#include "solveur2.h"
#include "solveurTableau2.h"

#define MIN_TAILLE_GRILLE 3
#define MAX_TAILLE_GRILLE 30
#define MAX_COUPS 100



int main()
{
	srand(time(NULL));

	int choix = -1;
	int continuer = 1;
	int xClic = 0, yClic = 0;

	SDL_Surface *ecran = initFenetre();
	SDL_Event event;

	menu(ecran);

	while(continuer) {
		SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym) {
            		case SDLK_ESCAPE:
						continuer = 0;
						break;
					default :
						break;
            	}
            	break;
            case SDL_MOUSEBUTTONDOWN:
            	if (event.button.button == SDL_BUTTON_LEFT) {
            		xClic = event.button.x ;
                    yClic = event.button.y ;
                    choix = choixMenu(xClic, yClic);
                }
                break;
        }
        if(choix >= 0) {
        	continuer = 0;
        }
	}
	maj(ecran);
	if(choix == 0) {
		jouer(ecran);
	}

	quitter();

	return 0;
}

void jouer(SDL_Surface *ecran) {
	Case **grille;
	TabComposanteConnexe tabCC = initTabComposanteConnexe();
	int taille = 0;
	int nbrCoups = 0;
	char nbCoupsStr[100];
	Couleur couleur = H;
	ComposanteConnexe *cc = NULL;
	int continuer = 1;
	int x = 0, y = 0;
	int xClic = 0, yClic = 0;
	SDL_Event event;

	taille = saisirTaille2D(ecran, "Entrez la taille de la grille,", MIN_TAILLE_GRILLE, MAX_TAILLE_GRILLE);

	/*Si on a quité pendant la saisie*/
	if(taille == -1) {
		quitter();
		exit(0);
	}

	nbrCoups = saisirTaille2D(ecran, "Nombre coups max,", 0, MAX_COUPS);

	/*Si on a quité pendant la saisie*/
	if(taille == -1) {
		quitter();
		exit(0);
	}

	grille = tableauVide(taille);
	grille = remplissageAleatoire(taille, grille);
	tabCC = listeComposanteConnexeGrille(grille, taille);
	tabCC = creeVoisins(tabCC, grille, taille);
	cc = rechercheElementTabComposanteConnexeAvecCase(getCaseGrille(grille, 0, 0), tabCC);
	/*solveurTableau2(tabCC, cc);*/
	/*solveur("./solution.txt", tabCC	,grille);*/
	/*On lance les deux solveurs comme ça plus de problèmes.*/
	/*afficheGrille(grille, taille);*/
	sprintf(nbCoupsStr, "Il vous reste %d coups", nbrCoups);

	afficheGrille2D(taille, grille, ecran, nbCoupsStr);

	while(nbrCoups >=0 && continuer != 0) {
		/*choix=saisirCouleur(nbrCoups);
		couleur = conversionCharCouleur(choix);*/
		/*afficheGrille(grille, taille);*/

		SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym) {
            		case SDLK_ESCAPE:
						continuer=0;
						break;
					default :
						break;
            	}
            	break;
            case SDL_MOUSEBUTTONDOWN:
            	if (event.button.button == SDL_BUTTON_LEFT) {
            		xClic = event.button.x ;
                    yClic = event.button.y ;
                    endroitClique(&y, &x, taille, xClic, yClic);
                    if(x < taille && x >= 0 && y < taille && y >= 0) {
                    	if(estVoisine(cc, rechercheElementTabComposanteConnexeAvecCase(getCaseGrille(grille, x, y), tabCC))) {
                    		couleur = getCouleurCase(getCaseGrille(grille, x, y));
							cc = changementCouleur(cc, &tabCC, couleur);
							nbrCoups = nbrCoups -1;
							if(nbrCoups == 0 && !testVictoire(tabCC, cc)) {
								sprintf(nbCoupsStr, "Vous avez perdu, echap pour quitter");
							}
							else if(testVictoire(tabCC, cc)){
								sprintf(nbCoupsStr, "Vous avez gagne, echap pour quitter");
							}
							else {
								sprintf(nbCoupsStr, "Il vous reste %d coups", nbrCoups);
							}
                    		afficheGrille2D(taille, grille, ecran, nbCoupsStr);
                    	}
                    }
                }
            break;

        }
	}
	destructeurTabComposanteConnexe(tabCC);
	liberationGrille(grille, taille);
}

int getche(void) {
	struct termios oldattr, newattr;
	int ch;
	tcgetattr( STDIN_FILENO, &oldattr );
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
	return ch;
}

char saisirCouleur(int nbrCoup){
	char c;
	printf("Il vous reste %d coups.\n",nbrCoup);
	printf ("Choisissez votre couleur : J pour Jaune, B pour Bleu, R pour Rouge, M pour Marron, V pour Vert et G pour Gris.\n");
	printf("Choix de la couleur : \n\n");
	c=getche();
	while (c!='j' && c!='J' && c!='r' && c!='R' && c!='m' && c!='M' && c!='b' && c!='B' && c!='g' && c!='G' && c!='v' && c!='V'){
		printf ("Cette couleur n'existe pas. Choisissez votre couleur :J pour Jaune, B pour Bleu, R pour Rouge, M pour Marron, V pour Vert et G pour Gris.\n");
		c=getche();
	}
	switch (c) {
		case 'j':
			return 'J';
		case 'r':
			return 'R';
		case 'm':
			return 'M';
		case 'b':
			return 'B';
		case 'g':
			return 'G';
		case 'v':
			return 'V';
		default :
			return c;
	}
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int saisirTaille() {
	char tmp[3];
	int ret = 0;
	int res = 0;
	int i = 0;

	ret = read(0, tmp, 3*sizeof(char)); /*lit la valeur entrée par le joueur, cette valeur est lu en temps que caractère.*/

	if(ret < 0) {
		perror("Erreur de saisie.\n\n");
		return 0;
	}
	else if(ret == 0) {
		printf("Rien n'a été saisi.\n\n");
		return 0;
	}
	else if(ret > 3){
		viderBuffer();
		ret = 3;
	}

	for(i = 0; i < ret; i++) {       /*convertie la valeur entrée par le joueur en temps que caractère en un entier*/
		if(tmp[i] > 47 && tmp[i] < 58) {
			res = res * 10 + (tmp[i] - 48);/*48 équivaut au 0*/
		}
	}

	return res;
}

int testTaille(int taille) {
	int min = 3;
	int max = 25;
	if(taille < min || taille > max) {
		printf("Merci de rentrer une taille entre %d et %d.\n\n", min, max);
		return 0;
	}
	return 1;
}

void afficheInterLigneDessus(int taille) {
	int i = 0;
	for(i = 0;i < taille;i++) {
		printf("----");
	}
	printf("-");
}

void afficheLigneDessus(Case **grille, int taille, int ligne) {
	int i = 0;
	for(i = 0;i < taille;i++) { /*affiche pour chaque case de la ligne la couleur et la délimitation de la case */
		printf("|");
		printf(" %c ", (conversionCouleurChar(getCouleurCase(getCaseGrille(grille, ligne, i)))));
	}
	printf("|");
}


void afficheGrille(Case **grille, int taille) {
	int i = 0;

	for(i = 0;i < taille;i++) {
		afficheInterLigneDessus(taille);
		printf("\n");
		afficheLigneDessus(grille, taille, i);
		printf("\n");
	}
	afficheInterLigneDessus(taille);
	printf("\n");
}

void setGrilleTest(Case **grille, ComposanteConnexe *cc) {
	ListeCase tmp = getCasesComposanteConnexe(cc);
	ListeComposanteConnexe voisins = getComposantesVoisinesComposanteConnexe(cc);
	while(!testListeCaseVide(tmp)) {
		setCouleur(getCaseGrille(grille, getXCase(getValeurListeCase(tmp)), getYCase(getValeurListeCase(tmp))), getCouleurCase(getValeurListeCase(tmp)));
		tmp = getSuivantListeCase(tmp);
	}
	while(!estVideListeComposanteConnexe(voisins)) {
		tmp = getCasesComposanteConnexe(getValeurListeComposanteConnexe(voisins));
		while(!testListeCaseVide(tmp)) {
			setCouleur(getCaseGrille(grille, getXCase(getValeurListeCase(tmp)), getYCase(getValeurListeCase(tmp))), getCouleurCase(getValeurListeCase(tmp)));
			tmp = getSuivantListeCase(tmp);
		}

		voisins = getSuivantListeComposanteConnexe(voisins);
	}
}

int saisirTaille2D(SDL_Surface *ecran, char *str1, int min, int max) {
	SDL_Event event;
	int taille = 0;
	char str2[100];
	int continuer = 1;
	sprintf(str2, "entre %d et %d :", min, max);
	saisieTaille2D(ecran, str1, str2);
	while(continuer != 0) {
		/*choix=saisirCouleur(nbrCoups);
		couleur = conversionCharCouleur(choix);*/
		/*afficheGrille(grille, taille);*/

		SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
                taille = -1;
                break;
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym) {
            		case SDLK_ESCAPE:
						continuer = 0;
						taille = -1;
						break;
					case SDLK_BACKSPACE :
						if(taille > 0) {
		            		taille = taille / 10;
		            		sprintf(str2, "entre %d et %d :%d", min, max, taille);
		            		saisieTaille2D(ecran, str1, str2);
		            	}
						break;
					case SDLK_RETURN :
						continuer = 0;
						break;
					/*Pour les touches 0 à 9 du clavier*/
					case SDLK_WORLD_64 :
						taille = changeTaille(ecran, str1, str2, 0, taille, min, max);
						break;
					case SDLK_AMPERSAND :
						taille = changeTaille(ecran, str1, str2, 1, taille, min, max);
						break;
					case SDLK_WORLD_73 :
						taille = changeTaille(ecran, str1, str2, 2, taille, min, max);
						break;
					case SDLK_QUOTEDBL :
						taille = changeTaille(ecran, str1, str2, 3, taille, min, max);
						break;
					case SDLK_QUOTE :
						taille = changeTaille(ecran, str1, str2, 4, taille, min, max);
						break;
					case SDLK_LEFTPAREN :
						taille = changeTaille(ecran, str1, str2, 5, taille, min, max);
						break;
					case SDLK_MINUS :
						taille = changeTaille(ecran, str1, str2, 6, taille, min, max);
						break;
					case SDLK_WORLD_72 :
						taille = changeTaille(ecran, str1, str2, 7, taille, min, max);
						break;
					case SDLK_UNDERSCORE :
						taille = changeTaille(ecran, str1, str2, 8, taille, min, max);
						break;
					case SDLK_WORLD_71 :
						taille = changeTaille(ecran, str1, str2, 9, taille, min, max);
						break;
					default :
						/*Pour le clavier numérique*/
		            	if(event.key.keysym.sym >= SDLK_KP0 && event.key.keysym.sym <= SDLK_KP9) {
		            		taille = changeTaille(ecran, str1, str2, event.key.keysym.sym - SDLK_KP0, taille, min, max);
		            	}
		            	/*pour les touches 0 à 9  du clavier, oui encore*/
		            	else if(event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) {
		            		taille = changeTaille(ecran, str1, str2, event.key.keysym.sym - SDLK_0, taille, min, max);
		            	}
		            	break;

            	}
            	break;
        }

        if(taille != -1) {
	        if(taille < min || taille > max) {
	        	continuer = 1;
	        }
	    }
    }
    return taille;
}

int changeTaille(SDL_Surface *ecran, char *str1, char *str2, int entierSaisi, int taille, int min, int max) {
	taille = 10 * taille + entierSaisi;
	if(taille <= max) {
		sprintf(str2, "entre %d et %d : %d", min, max, taille);
		saisieTaille2D(ecran, str1, str2);
	}
	else {
		taille = taille / 10;
	}
	return taille;
}
