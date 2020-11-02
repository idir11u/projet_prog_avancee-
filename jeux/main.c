#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "gestion_terrain.h"

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
	creer_SDL_Renderer_terrain(&t,ligne,colonne);
	init_terrain(&t,ligne,colonne,tab);
	SDL_Renderer* ecran ;
	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
	// Charger l’image
	Uint8 r = 0, g = 255, b = 255;
	t.image = charger_image_transparente("pavage.bmp", ecran,r,g,b);

	//Boucle principale
	while(!terminer)
	{
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
				}	
			}
		SDL_RenderClear(ecran);
		for (int i = 0; i < ligne; i++)
		{
			for (int j=0 ; j<colonne ; j++)
			{
				SDL_RenderCopy(ecran,t.image, &(t.SrcR_terrain[i][j]),&(t.DestR_terrain[i][j]));
			}
		}
		SDL_RenderPresent(ecran);
	}
	desallouer_SDL_Renderer_terrain(&t,ligne);
	desallouer_tab_2D(tab,ligne);
	// Fermer la police et quitter SDL_ttf
	SDL_DestroyTexture(t.image);
	// Libération de l’écran (renderer)
	SDL_DestroyRenderer(ecran);
	// Quitter SDL 
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
