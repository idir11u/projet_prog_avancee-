/**
* \file  fonctios_SDL.h
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque graphic.h qui fait gestion de l'affichage dans le jeux  
*/
#ifndef GRAPHIC_H
#define  GRAPHIC_H

#include<SDL2/SDL.h>
#include "fonctions_SDL.h"
#include "world.h"
#include "message.h"

void init_textures(world_t *world,SDL_Renderer * renderer);
void handle_events(world_t *world,SDL_Event *evenements);
void update_data(world_t *world);
void refresh_graphic(world_t *world,SDL_Renderer * renderer,TTF_Font *font,message_t *msg);
void clear_textures(world_t *world);




#endif 