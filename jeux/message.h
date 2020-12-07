/**
* \file  fonctios_SDL.c
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque d'fonctios_SDL . 
*/
#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include"fonctions_SDL.h"
#include"affichage_text.h"


#ifndef MESSAGE_H
#define MESSAGE_H


struct message_s
{
	text_t game_over;
	text_t you_win;
	text_t score;
	text_t score_chiffre;

};
typedef struct message_s message_t;	

void init_message(message_t *msg,SDL_Renderer* renderer,TTF_Font *font);
void update_message(text_t *text ,SDL_Renderer* renderer,TTF_Font *font,int chiffre);
void clean_message(message_t *msg);

#endif 
