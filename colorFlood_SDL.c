#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include "Grille.h"

int autoDraw=0;

/* px, py coordonnées haut, gauche du pixel*/
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x=px;
    rect.y=py;
    rect.h=rect.w=size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}

void fillScreen(SDL_Surface *ecran, int r, int g, int b) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}

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
	SDL_WM_SetCaption("exemple SDL", NULL);

  fillScreen(ecran, 0,0,0);
  drawRectangle(ecran, 250, 250, 5, 0, 255, 255);
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

  TTF_Init();

  if(TTF_Init() == -1){
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }

  return ecran;
}

/*i et j sont les coordonnées de la case cliquée*/
void endroitClique(int *i, int* j, int nombre_Cases, int x_clique, int y_clique){
  int nbPixelCase = 500/nombre_Cases;

  *i = (x_clique - 50)/nbPixelCase;
  *j = (y_clique - 50)/nbPixelCase;

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
  SDL_Color couleurNoire = {0, 0, 0};
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
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
        SDL_BlitSurface(carre, NULL, ecran, &position);
      }
      if(getCouleurCase(getCaseGrille(tab,i,j))==V){
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
        SDL_BlitSurface(carre, NULL, ecran, &position);
      }
      if(getCouleurCase(getCaseGrille(tab,i,j))==B){
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
        SDL_BlitSurface(carre, NULL, ecran, &position);
      }
      if(getCouleurCase(getCaseGrille(tab,i,j))==J){
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 240, 195, 0));
        SDL_BlitSurface(carre, NULL, ecran, &position);
      }
      if(getCouleurCase(getCaseGrille(tab,i,j))==M){
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 132, 46, 27));
        SDL_BlitSurface(carre, NULL, ecran, &position);
      }
      if(getCouleurCase(getCaseGrille(tab,i,j))==G){
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 80, 80, 80));
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