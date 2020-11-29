#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include  "constante.h"
#include <stdbool.h>
#include "world.h"
#include "graphic.h"
#include "message.h"

int main(int argc, char *argv[]){
	
	SDL_Window* fenetre;  // Déclaration de la fenêtre
	SDL_Event evenements; // Événements liés à la fenêtre
	SDL_Renderer* ecran ;
	world_t world;
	init_SDL();
	init_world(&world);
	fenetre = creer_window(HAUTEUR_ECRAN,LARGEUR_ECRAN);
	ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("./arial.ttf",35);
	message_t msg;
	init_message(&msg,ecran,font);
	//Charger l’image
	init_textures(&world,ecran);
	printf("nbr ennemy %i\n",world.ennemies.nbr_ennemies);
	while(!world.terminer)
	{
		handle_events(&world,&evenements);
		update_world(&world);
		//world.ennemy.DestR_sprite.x++;
		refresh_graphic(&world,ecran,&msg);
		pause(15);// une pause du programe pendant 10 ms  
	}
	clean_world(&world);
	clear_textures(&world);
	clean_message(&msg);
	// Fermer la police et quitter SDL_ttf
	TTF_CloseFont( font );
	TTF_Quit();
	// Libération de l’écran (renderer)
	SDL_DestroyRenderer(ecran);
	// Quitter SDL 
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
