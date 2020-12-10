/**
* \file  jeu.c
* \author  Ait Aider Zinedine && Idir Walid Hakim
* \Brief bibliotheque qui fait la gestion du jeux . 
*/

#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include"fonctions_SDL.h"
#include"constante.h"
#include"message.h"
#include"world.h"
#include"jeu.h"


void init_XYWH(SDL_Rect *rect,int x,int y,int w,int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;

}


void init_jeux(jeu_t *jeu)
{
	jeu->start = false;
	jeu->Quit = false;
	init_XYWH(&(jeu->background.SrcR_image),0,0,BACKGROUND_LARGEUR,BACKGROUND_HAUTEUR);
	init_XYWH(&(jeu->background.DestR_image),0,0,LARGEUR_ECRAN,HAUTEUR_ECRAN);

	init_XYWH(&(jeu->image_start.SrcR_image),0,0,IMAGE_START_LARGEUR,IMAGE_START_HAUTEUR);
	init_XYWH(&(jeu->image_start.DestR_image),(3*LARGEUR_ECRAN)/8,HAUTEUR_ECRAN/4,LARGEUR_ECRAN/4,HAUTEUR_ECRAN/8);

	init_XYWH(&(jeu->image_score.SrcR_image),0,0,IMAGE_START_LARGEUR,IMAGE_START_HAUTEUR);
	init_XYWH(&(jeu->image_score.DestR_image),(3*LARGEUR_ECRAN)/8,(7*HAUTEUR_ECRAN)/16,LARGEUR_ECRAN/4,HAUTEUR_ECRAN/8);

	init_XYWH(&(jeu->image_quit.SrcR_image),0,0,IMAGE_START_LARGEUR,IMAGE_START_HAUTEUR);
	init_XYWH(&(jeu->image_quit.DestR_image),(3*LARGEUR_ECRAN)/8,(5*HAUTEUR_ECRAN)/8,LARGEUR_ECRAN/4,HAUTEUR_ECRAN/8);

}

