#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "gestion_terrain.h"
#include "constante.h"
#include <math.h>
#include <stdbool.h>


struct sprite_s 
{
	SDL_Texture* image;
	SDL_Rect SrcR_sprite;
	SDL_Rect DestR_sprite;
};
typedef struct sprite_s sprite_t;


void init_sprite(sprite_t * sprite  , int h_terrain ,int w_terrain)
{
	sprite->DestR_sprite.x = 0;
	sprite->DestR_sprite.y = 0;
	sprite->DestR_sprite.h = h_terrain;	
	sprite->DestR_sprite.w = w_terrain;
	sprite->SrcR_sprite.x = 0;
	sprite->SrcR_sprite.y = 0;
	sprite->SrcR_sprite.w = LARGEUR_IMAGE_HEROS/NBR_VERTIC_IMAGE_HEROS;	
	sprite->SrcR_sprite.h = HAUTEUR_IMAGE_HEROS / NBR_HORIS_IMAGE_HEROS;
}

void depacemnt_bordure(sprite_t* sprite,int Hauteur_ecran,int Largeur_ecran)
{

	if(sprite->DestR_sprite.x < 0)
		sprite->DestR_sprite.x = 0;
	if( sprite->DestR_sprite.x > Largeur_ecran-sprite->DestR_sprite.w)
		sprite->DestR_sprite.x = Largeur_ecran-sprite->DestR_sprite.w ;
	if (sprite->DestR_sprite.y<0)
		sprite->DestR_sprite.y = 0;
	if  (sprite->DestR_sprite.y> Hauteur_ecran-sprite->DestR_sprite.h)
		sprite->DestR_sprite.y = Hauteur_ecran-sprite->DestR_sprite.h;
}

bool collision_murs(sprite_t sprite, terrain_t terrain, int ligne, int colonne)
{
	int x1,x2,y1,y2;
	x1 = sprite.DestR_sprite.x + sprite.DestR_sprite.w/2;//l'abcsice du centre du sprite
	y1 = sprite.DestR_sprite.y + sprite.DestR_sprite.h/2;//l'ordonnée du centre du sprite
	for (int i = 0; i < ligne; ++i)
	{
		for (int j = 0; j < colonne; ++j)
		{
			if (terrain.SrcR_terrain[i][j].x != 0 || terrain.SrcR_terrain[i][j].y != 0 ) // differente de la terre
			{
				x2 = terrain.DestR_terrain[i][j].x + terrain.DestR_terrain[i][j].w/2; // l'abscice du centre du du mur(i,j) 
				y2 = terrain.DestR_terrain[i][j].y + terrain.DestR_terrain[i][j].h/2; // l'ordonnée du centre du du mur(i,j) 
				if (abs(x1-x2) < (sprite.DestR_sprite.w + terrain.DestR_terrain[i][j].w)/2)
					if (abs(y1-y2) < (sprite.DestR_sprite.h + terrain.DestR_terrain[i][j].h)/2)
						return true;
			}
		}
	}
	return false;
	
}
/*
{
	if (SrcR_murs[i][j]->x ==0 && SrcR_murs[i][j]->y ==0 )
		printf("vert\n");
	else 
		printf("pas vert\n");
}
*/

int main(int argc, char *argv[]){

	int colonne=0,ligne=0;
	taille_fichier("terrain.txt",&ligne,&colonne);
	printf("%i \n",colonne);
	printf("%i \n",ligne);
	SDL_Window* fenetre;  // Déclaration de la fenêtre
	SDL_Event evenements; // Événements liés à la fenêtre
	
	bool terminer = false;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
	{
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	// Créer la fenêtre
	
	char **tab = lire_fichier("terrain.txt");
	fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,32*colonne,32*ligne, SDL_WINDOW_RESIZABLE);
	if(fenetre == NULL) // En cas d’erreur
	{
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	// Mettre en place un contexte de rendu de l’écran
	terrain_t t; /*-----------------------------------------------------------------*/
	sprite_t joueur;
	creer_SDL_Renderer_terrain(&t,ligne,colonne);
	init_terrain(&t,ligne,colonne,tab);
	SDL_Renderer* ecran ;
	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
	// Charger l’image
	Uint8 r = 0, g = 255, b = 255;
	t.image = charger_image_transparente("pavage.bmp", ecran,r,g,b);
	joueur.image = charger_image_transparente("sprite.bmp", ecran,r,g,b);
	init_sprite(&joueur,32,32);

	//Boucle principale
	while(!terminer)
	{
		int i ;
		while( SDL_PollEvent( &evenements ) )
			switch(evenements.type)
			{
				case SDL_QUIT:
					terminer = true; break;
				case SDL_KEYDOWN:
				switch(evenements.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					case SDLK_q:
						terminer = true;  break;
					case SDLK_UP:
						joueur.DestR_sprite.y = joueur.DestR_sprite.y - 8 ;
						if (collision_murs(joueur,t,ligne,colonne))
							joueur.DestR_sprite.y = joueur.DestR_sprite.y + 8 ; 

						break;

					case SDLK_DOWN: 
						joueur.DestR_sprite.y = joueur.DestR_sprite.y + 8 ;
						if (collision_murs(joueur,t,ligne,colonne))
							joueur.DestR_sprite.y = joueur.DestR_sprite.y - 8; 
						break;
					case SDLK_LEFT: 
						joueur.DestR_sprite.x  = joueur.DestR_sprite.x - 8 ;  
						if (collision_murs(joueur,t,ligne,colonne))
							joueur.DestR_sprite.x = joueur.DestR_sprite.x + 8; 
						break;
					case SDLK_RIGHT:  
						joueur.DestR_sprite.x  = joueur.DestR_sprite.x + 8 ; 
						if (collision_murs(joueur,t,ligne,colonne))
								joueur.DestR_sprite.x = joueur.DestR_sprite.x - 8; 
						break;
				}	
			}
		depacemnt_bordure(&(joueur),ligne*32,colonne*32);
		SDL_RenderClear(ecran);
		for (int i = 0; i < ligne; i++)
		{
			for (int j=0 ; j<colonne ; j++)
			{
				SDL_RenderCopy(ecran,t.image, &(t.SrcR_terrain[i][j]),&(t.DestR_terrain[i][j]));
			}
			SDL_RenderCopy(ecran,joueur.image, &(joueur.SrcR_sprite), &(joueur.DestR_sprite) );
		}
		SDL_RenderPresent(ecran);
	}
	desallouer_SDL_Renderer_terrain(&t,ligne);
	desallouer_tab_2D(tab,ligne);
	// Fermer la police et quitter SDL_ttf
	SDL_DestroyTexture(t.image);
	SDL_DestroyTexture(joueur.image);
	// Libération de l’écran (renderer)
	SDL_DestroyRenderer(ecran);
	// Quitter SDL 
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
