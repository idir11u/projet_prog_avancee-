#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "fonctions_SDL.h"
#include"world.h"
#include"constante.h"
#include<SDL2/SDL.h>
#include "message.h"
void init_textures(world_t *world,SDL_Renderer * renderer)
{
	Uint8 r = 0, g = 255, b = 255;
	world->terrain.image = charger_image_transparente("pavage.bmp", renderer,r,g,b);
	world->heros.image = charger_image_transparente("sprite.bmp", renderer,r,g,b);
	for(int i = 0; i< world->ennemies.nbr_ennemies; i++)
	{
		world->ennemies.sprite[i].image = charger_image_transparente("sprite.bmp", renderer,r,g,b);
	}
	r = 255, g = 255, b = 255;
	world->tresor.image = charger_image_transparente("tresor.bmp", renderer,r,g,b);

}

void handle_events(world_t *world,SDL_Event *evenements)
{
	while( SDL_PollEvent( evenements ) )
			switch(evenements->type)
			{
				case SDL_QUIT:
					world->terminer = true; break;
				case SDL_KEYDOWN:                                                      
				switch(evenements->key.keysym.sym)
				{
					case SDLK_ESCAPE:
					case SDLK_q:
						world->terminer = true;  break;
					case SDLK_UP:
						if (world->heros.est_visible == 1 && !collision(&(world->heros),&(world->tresor))){
							world->heros.DestR_sprite.y = world->heros.DestR_sprite.y - 4 ;
							if (collision_murs(world->heros,world->terrain,world->ligne,world->colonne))
								world->heros.DestR_sprite.y = ((world->heros.DestR_sprite.y/world->heros.DestR_sprite.h)+1)*world->heros.DestR_sprite.h;
							update_farmes(&(world->heros.farme),NBR_HORIS_IMAGE_HEROS,1,2);// 
							world->heros.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->heros.farme.cpt;
							world->heros.SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-world->heros.SrcR_sprite.w ;
						}
						break;
					case SDLK_DOWN: 
						if (world->heros.est_visible == 1 && !collision(&(world->heros),&(world->tresor))){
							world->heros.DestR_sprite.y = world->heros.DestR_sprite.y + 4 ;
							if (collision_murs(world->heros,world->terrain,world->ligne,world->colonne))
								world->heros.DestR_sprite.y = (world->heros.DestR_sprite.y/world->heros.DestR_sprite.h)*world->heros.DestR_sprite.h;
							update_farmes(&(world->heros.farme),NBR_HORIS_IMAGE_HEROS,0,2);// 
							world->heros.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->heros.farme.cpt;
							world->heros.SrcR_sprite.y = 0;
						}	
						break;
					case SDLK_LEFT:
						if (world->heros.est_visible == 1 && !collision(&(world->heros),&(world->tresor))){
							world->heros.DestR_sprite.x  = world->heros.DestR_sprite.x - 4 ;  
							if (collision_murs(world->heros,world->terrain,world->ligne,world->colonne))
								world->heros.DestR_sprite.x = ((world->heros.DestR_sprite.x/world->heros.DestR_sprite.w)+1)*world->heros.DestR_sprite.w; // pour le coller au murs si il ya une collision avec le mur le plus 1 car c'est a gauche 
							update_farmes(&(world->heros.farme),NBR_HORIS_IMAGE_HEROS,2,2);// 
							world->heros.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->heros.farme.cpt;
							world->heros.SrcR_sprite.y =HAUTEUR_IMAGE_HEROS-3*world->heros.SrcR_sprite.w ;
						}
						break;
					case SDLK_RIGHT: 
						if (world->heros.est_visible == 1 && !collision(&(world->heros),&(world->tresor))){
							world->heros.DestR_sprite.x  = world->heros.DestR_sprite.x + 4 ; 
							if (collision_murs(world->heros,world->terrain,world->ligne,world->colonne))
									world->heros.DestR_sprite.x = (world->heros.DestR_sprite.x/world->heros.DestR_sprite.w)*world->heros.DestR_sprite.w; // pour le coller au murs si il ya une collision avec le mur 
							update_farmes(&(world->heros.farme),NBR_HORIS_IMAGE_HEROS,3,2);// *
							world->heros.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->heros.farme.cpt;
							world->heros.SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-2*world->heros.SrcR_sprite.w ;
						}
						break;
					
				} 
				
			}
}

void update_data(world_t *world)
{
		depacemnt_bordure(&(world->heros),world->ligne*40,world->colonne*40);
}

void refresh_graphic(world_t *world,SDL_Renderer * renderer,message_t *msg)
{
	SDL_RenderClear(renderer);
	
	for (int i = 0; i < world->ligne; i++)
	{
		for (int j=0 ; j<world->colonne ; j++)
		{
			SDL_RenderCopy(renderer,world->terrain.image, &(world->terrain.SrcR_terrain[i][j]),&(world->terrain.DestR_terrain[i][j]));
		}
	}
	for(int i = 0 ; i<world->ennemies.nbr_ennemies;i++)
	{
		if(world->ennemies.sprite[i].est_visible == 1)
		{
			SDL_RenderCopy(renderer,world->ennemies.sprite[i].image, &(world->ennemies.sprite[i].SrcR_sprite), &(world->ennemies.sprite[i].DestR_sprite) );
		}
	
	}

	if(world->heros.est_visible == 1) 
		SDL_RenderCopy(renderer,world->heros.image, &(world->heros.SrcR_sprite), &(world->heros.DestR_sprite) );
	SDL_RenderCopy(renderer,world->tresor.image, &(world->tresor.SrcR_sprite), &(world->tresor.DestR_sprite) );
	if(world->heros.est_visible == 0)
	{
		SDL_RenderCopy(renderer,msg->game_over.text,NULL,&(msg->game_over.DestR_text));
	}		
	else if(collision(&(world->heros),&(world->tresor)))
	{
		if (world->tresor.farme.cpt<3)
		{
			if(world->tresor.farme.cpt == 2)
			{
				world->tresor.farme.stop = true;
			}
			update_farmes(&(world->tresor.farme),NBR_HORIS_IMAGE_TRESOR,0,15);// *
			world->tresor.SrcR_sprite.x = (LARGEUR_IMAGE_TRESOR/NBR_HORIS_IMAGE_TRESOR)*world->tresor.farme.cpt;
			world->tresor.SrcR_sprite.y = 0 ;
			SDL_RenderCopy(renderer,world->tresor.image, &(world->tresor.SrcR_sprite), &(world->tresor.DestR_sprite));
		}		
	}
	if(world->tresor.farme.stop)
	{
		SDL_RenderCopy(renderer,msg->you_win.text,NULL,&(msg->game_over.DestR_text));
	}
	SDL_RenderPresent(renderer);
}




void clear_textures(world_t *world)
{
	SDL_DestroyTexture(world->terrain.image);
	SDL_DestroyTexture(world->heros.image);
	for(int i = 0; i< world->ennemies.nbr_ennemies; i++)
	{
		SDL_DestroyTexture(world->ennemies.sprite[i].image);
	}
	SDL_DestroyTexture(world->tresor.image);
}

