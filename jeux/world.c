
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"
#include"gestion_terrain.h"
#include"world.h"
#include"constante.h"
#include"gestion_farmes.h" 




void init_sprite(sprite_t * sprite  , int h_terrain ,int w_terrain,int x,int y)
{
	sprite->DestR_sprite.x = x;
	sprite->DestR_sprite.y = y;
	sprite->DestR_sprite.h = h_terrain;	
	sprite->DestR_sprite.w = w_terrain;
	sprite->SrcR_sprite.x = x;
	sprite->SrcR_sprite.y = y;
	sprite->SrcR_sprite.w = LARGEUR_IMAGE_HEROS/ NBR_HORIS_IMAGE_HEROS;	
	sprite->SrcR_sprite.h = HAUTEUR_IMAGE_HEROS / NBR_VERTIC_IMAGE_HEROS;
	init_farme(&(sprite->farme));                                           //mazal
}


void init_world(world_t *world)
{

	//il faut que ligne et colnne
	world->terminer = false ; 
	taille_fichier("terrain.txt",&(world->ligne),&(world->colonne));
	world->tab = lire_fichier("terrain.txt");
	init_terrain(&(world->terrain),world->ligne,world->colonne,world->tab);
	init_sprite(&(world->heros),world->terrain.DestR_terrain[0][0].h,world->terrain.DestR_terrain[0][0].w,0,0);

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

void update_world(world_t *world)
{


}

void clean_world(world_t *world)
{
	desallouer_tab_2D(world->tab,world->ligne);
	desallouer_SDL_Renderer_terrain(&(world->terrain),world->ligne);
}


