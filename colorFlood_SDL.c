#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include "Grille.h"

SDL_Surface* initFenetre() {
  SDL_Surface *ecran = NULL;
  const SDL_VideoInfo* info = NULL;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        /* Failed, exit. */
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        SDL_Quit( );
    }
    info = SDL_GetVideoInfo( );
    if( !info ) {
        /* This should probably never happen. */
        fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
        SDL_Quit( );
    }

	ecran=SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("Color flood GinGinMoney", NULL);

  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  SDL_Flip(ecran);

  TTF_Init();

  if(TTF_Init() == -1){
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }

  return ecran;
}

void maj(SDL_Surface *ecran) {
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  SDL_Flip(ecran);
}

void menu(SDL_Surface *ecran) {
  SDL_Rect position;
  SDL_Surface *texte = NULL;
  SDL_Surface *choixMenu = NULL;
  SDL_Surface *choixMenuBack = NULL;
  TTF_Font *police = NULL;
  SDL_Color couleurNoire;
  couleurNoire.r = 0;
  couleurNoire.g = 0;
  couleurNoire.b = 0;
  choixMenu = SDL_CreateRGBSurface(SDL_HWSURFACE, 140, 40, 32, 0, 0, 0, 0);
  choixMenuBack = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 50, 32, 0, 0, 0, 0);
  police = TTF_OpenFont("LinLibertine.ttf", 32);
  if(!police) {
    printf("Erreur lors du chargement de la police");
  }

  position.x = 120;
  position.y = 50;

  texte = TTF_RenderText_Blended(police, "Bienvenue dans le color flood", couleurNoire);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  SDL_FreeSurface(texte);
  position.x += 50;
  position.y += 50;
  texte = TTF_RenderText_Blended(police, "de GinGinMoney!!", couleurNoire);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  SDL_FreeSurface(texte);

  position.x = 225;
  position.y = 250;
  SDL_FillRect(choixMenuBack, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
  SDL_BlitSurface(choixMenuBack, NULL, ecran, &position);
  position.x += 5;
  position.y += 5;
  SDL_FillRect(choixMenu, NULL, SDL_MapRGB(ecran->format, 206, 206, 206));
  SDL_BlitSurface(choixMenu, NULL, ecran, &position);
  position.x += 30;
  texte = TTF_RenderText_Blended(police, "Jouer", couleurNoire);
  SDL_BlitSurface(texte, NULL, ecran, &position);

  /*SDL_FreeSurface(texte);*/

  SDL_Flip(ecran);

  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(choixMenu);
  SDL_FreeSurface(choixMenuBack);
}

void saisieTaille2D(SDL_Surface *ecran, char *str1, char *str2) {
  SDL_Rect position;
  SDL_Surface *texte = NULL;
  SDL_Surface *cacheTexte = NULL;
  TTF_Font *police = NULL;
  SDL_Color couleurNoire;
  couleurNoire.r = 0;
  couleurNoire.g = 0;
  couleurNoire.b = 0;
  cacheTexte = SDL_CreateRGBSurface(SDL_HWSURFACE, 450, 50, 32, 0, 0, 0, 0);
  police = TTF_OpenFont("LinLibertine.ttf", 32);
  if(!police) {
    fprintf(stderr, "Erreur lors du chargement de la police");
  }

  position.x=60;
  position.y=250;
  SDL_FillRect(cacheTexte, NULL, SDL_MapRGB(ecran->format, 250, 250, 250));
  SDL_BlitSurface(cacheTexte, NULL, ecran, &position);
  texte = TTF_RenderText_Blended(police, str1, couleurNoire);
  SDL_BlitSurface(texte, NULL, ecran, &position);

  SDL_FreeSurface(texte);

  position.y += 40;
  SDL_FillRect(cacheTexte, NULL, SDL_MapRGB(ecran->format, 250, 250, 250));
  SDL_BlitSurface(cacheTexte, NULL, ecran, &position);
  texte = TTF_RenderText_Blended(police, str2, couleurNoire);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  SDL_Flip(ecran);

  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(cacheTexte);
}

/*i et j sont les coordonnées de la case cliquée*/
void endroitClique(int *i, int* j, int nombre_Cases, int x_clique, int y_clique){
  int nbPixelCase = 500/nombre_Cases;

  if(x_clique < 50 || x_clique > 550) {
    *i = -1;
    *j = -1;
  }
  else if(y_clique < 50 || y_clique > 550) {
    *i = -1;
    *j = -1;
  }
  else {
    *i = (x_clique - 50)/nbPixelCase;
    *j = (y_clique - 50)/nbPixelCase;
  }
}

void quitter(){
  TTF_Quit();
  SDL_Quit();
}

void afficheGrille2D(int tailleGrille, Case **tab, SDL_Surface *ecran, char *str){
  int taille = 500;
  int tailleCarre = taille/tailleGrille;
  SDL_Rect position;
  position.x = 50;
  position.y = 50;
  int i;
  int j;
  SDL_Surface *carre = NULL;
  SDL_Surface *texte = NULL;
  SDL_Surface *cacheTexte = NULL;
  TTF_Font *police = NULL;
  /*SDL_Color fond = {255,255,255};*/
  SDL_Color couleurNoire;
  couleurNoire.r = 0;
  couleurNoire.g = 0;
  couleurNoire.b = 0;
  carre = SDL_CreateRGBSurface(SDL_HWSURFACE, tailleCarre, tailleCarre, 32, 0, 0, 0, 0);
  cacheTexte = SDL_CreateRGBSurface(SDL_HWSURFACE, 450, 50, 32, 0, 0, 0, 0);
  police = TTF_OpenFont("LinLibertine.ttf", 32);
  if(!police) {
    printf("Erreur lors du chargement de la police");
  }
  SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  SDL_BlitSurface(carre, NULL, ecran, &position);

  for (i=0;i<tailleGrille;i++){
    for(j=0;j<tailleGrille;j++){
      if(getCouleurCase(getCaseGrille(tab,i,j))==R){
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 237, 0, 0));
        SDL_BlitSurface(carre, NULL, ecran, &position);
      }
      if(getCouleurCase(getCaseGrille(tab,i,j))==V){
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 20, 148, 20));
        SDL_BlitSurface(carre, NULL, ecran, &position);
      }
      if(getCouleurCase(getCaseGrille(tab,i,j))==B){
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 16, 52, 166));
        SDL_BlitSurface(carre, NULL, ecran, &position);
      }
      if(getCouleurCase(getCaseGrille(tab,i,j))==J){
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 252, 220, 18));
        SDL_BlitSurface(carre, NULL, ecran, &position);
      }
      if(getCouleurCase(getCaseGrille(tab,i,j))==M){
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 91, 60, 17));
        SDL_BlitSurface(carre, NULL, ecran, &position);
      }
      if(getCouleurCase(getCaseGrille(tab,i,j))==G){
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 175, 175, 175));
        SDL_BlitSurface(carre, NULL, ecran, &position);
      }
      position.x+=tailleCarre;
    }
    position.x=50;
    position.y+=tailleCarre;
  }
  position.x=40;
  position.y=550;
  SDL_FillRect(cacheTexte, NULL, SDL_MapRGB(ecran->format, 250, 250, 250));
  SDL_BlitSurface(cacheTexte, NULL, ecran, &position);
  texte = TTF_RenderText_Blended(police, str, couleurNoire);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  SDL_Flip(ecran);
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(carre);
  SDL_FreeSurface(cacheTexte);
}

int choixMenu(int x, int y) {
  if(x >= 225 && x <= 225 + 150 && y >= 250 && y <= 250 + 50) {
    return 0;
  }
  return -1;
}

/*int main(int argc, char *argv[]) {
  srand(time(NULL));


    int tailleGrille = 20;


  Case **tab=tableauVide(tailleGrille);
  tab = remplissageAleatoire(tailleGrille,tab);
	int continuer = 1;
  SDL_Surface *ima=NULL;
  SDL_Event event;

  SDL_Surface *ecran = initFenetre();

    ima = SDL_LoadBMP("./cerise.bmp");

    afficheGrille2D(tailleGrille,tab,ecran);

    while (continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym) {
            		case SDLK_ESCAPE:
						continuer=0; break;
            	}
            	break;
        }
    }
	quitter();

	return 0;
}
*/
