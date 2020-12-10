/**
* \file  fonctios_SDL.h
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque graphic.h qui fait gestion de l'affichage dans le jeux  
*/
#ifndef JEU_H
#define  JEU_H

#include<SDL2/SDL.h>
#include"fonctions_SDL.h"
#include<stdbool.h>
#include"world.h"
#include"message.h"

struct image_s
{
	SDL_Texture* image;
	SDL_Rect SrcR_image;
	SDL_Rect DestR_image;

};
typedef struct image_s image_t;

struct jeu_s
{
	bool start;
	bool Quit;
	world_t world;
	message_t message;
	image_t background;
	image_t image_start;
	image_t image_score;
	image_t image_quit;
};
typedef struct jeu_s jeu_t;

void init_jeux(jeu_t *jeu);

#endif 
