/**
* \file  fonctios_SDL.h
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque world.h qui fait la gestion des données de jeux
*/

#ifndef WORLD_H
#define  WORLD_H
#include"gestion_terrain.h"


struct  farme_s 
{
	int cpt; //le numero de l'image actuel qu'on afffiche sur la ligne
	int dist; // est la distination 0 DOWN / 1 UP / 2 LEFT / 3 RIGHT.
};
typedef struct farme_s farme_t;

struct sprite_s 
{
	farme_t farme;
	SDL_Texture* image;
	SDL_Rect SrcR_sprite;
	SDL_Rect DestR_sprite;
};
typedef struct sprite_s sprite_t;

struct world_s 
{
	bool terminer;
	int ligne,colonne;//nombre de ligne et de colonne de la matrice q'on va lire depuis de fichier .txt du terrain
	char ** tab; // la matrice de du jeux 
	terrain_t terrain;
	sprite_t heros; 

};

typedef struct world_s world_t;

void init_farme(farme_t *farme );
void init_sprite(sprite_t * sprite  , int h_terrain ,int w_terrain);
void init_world(world_t *world);
void depacemnt_bordure(sprite_t* sprite,int Hauteur_ecran,int Largeur_ecran);
bool collision_murs(sprite_t sprite, terrain_t terrain, int ligne, int colonne);
void update_farmes(farme_t *farme,int nbr_image_horisental,int i);
void update_world(world_t *world);
void clean_world(world_t *world);

#endif 
