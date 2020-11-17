#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "gestion_terrain.h"
#include  "constante.h"
#include <math.h>
#include <stdbool.h>
#include "world.h"
#include "graphic.h"



int main(int argc, char *argv[]){
	
	SDL_Window* fenetre;  // Déclaration de la fenêtre
	SDL_Event evenements; // Événements liés à la fenêtre
	SDL_Renderer* ecran ;
	world_t world;
	init_SDL();
	init_world(&world);
	fenetre = creer_window(world.ligne,world.colonne);;
	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
	//Charger l’image
	init_textures(&world,ecran);
	for (int i = 0 ; i < world.terrain.chemin.nbr_sommet;i++)
	{
		printf("[%i]<---",world.terrain.chemin.tab[i]);
	}
	while(!world.terminer)
	{
		handle_events(&world,&evenements);
		update_data(&world);
		refresh_graphic(&world,ecran);
	}
	clean_world(&world);
	clear_textures(&world);
	// Libération de l’écran (renderer)
	SDL_DestroyRenderer(ecran);
	// Quitter SDL 
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
