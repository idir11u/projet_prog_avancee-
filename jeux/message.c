/**
* \file  fonctios_SDL.c
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque d'fonctios_SDL . 
*/
#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include"fonctions_SDL.h"
#include"constante.h"
#include"message.h"

void init_message(message_t *msg,SDL_Renderer* renderer,TTF_Font *font)
{
	init_text(&(msg->game_over),"Game over",renderer,font,LARGEUR_ECRAN/4,HAUTEUR_ECRAN/4+HAUTEUR_ECRAN/8,LARGEUR_ECRAN/2,HAUTEUR_ECRAN/4); //HAUTEUR_ECRAN*(3/8)
	init_text(&(msg->you_win),"You Win",renderer,font,20,20,100,20);

}	

void clean_message(message_t *msg)
{
	SDL_DestroyTexture(msg->game_over.text);
	SDL_DestroyTexture(msg->you_win.text);

}

