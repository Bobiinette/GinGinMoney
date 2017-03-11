#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include "Grille.h"

int autoDraw=0;

/* px, py coordonnées haut, gauche de la texture*/
void drawTexture(SDL_Surface *ecran, int px, int py, SDL_Surface *ima) {
	SDL_Rect rect;
    rect.x=px;
    rect.y=py;
	SDL_BlitSurface(ima, NULL, ecran, &rect);
	SDL_Flip(ecran);
}

/* px, py coordonnées haut, gauche du pixel*/
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x=px;
    rect.y=py;
    rect.h=rect.w=size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}

/* px, py coordonnées haut, gauche du pixel*/
void drawPixel(SDL_Surface *ecran, int px, int py, int r, int g, int b) {
    drawRectangle(ecran,  px,  py, 1,  r,  g,  b);
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

void quitter(){
  TTF_Quit();
  SDL_Quit();
}

void afficheGrille2D(int tailleGrille, Case **tab, SDL_Surface *ecran){
  int taille = 500;
  int tailleCarre = taille/tailleGrille;
  SDL_Rect position;
  position.x = 50;
  position.y = 50;
  int i;
  int j;
  SDL_Surface *carre = NULL;
  SDL_Surface *texte =NULL;
  TTF_Font *police = NULL;
  /*SDL_Color fond = {255,255,255};*/
  SDL_Color couleurNoire = {0, 0, 0};
  carre = SDL_CreateRGBSurface(SDL_HWSURFACE, tailleCarre, tailleCarre, 32, 0, 0, 0, 0);
  police = TTF_OpenFont("napo.ttf", 14);
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
  position.x=0;
  position.y=0;
  texte = TTF_RenderText_Blended(police, "Salut les Zér0s !", couleurNoire/*, fond*/);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  SDL_Flip(ecran);
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(carre);
}

int main(int argc, char *argv[]) {
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
