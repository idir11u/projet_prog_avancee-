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
	init_text(&(msg->you_win),"You Win",renderer,font,LARGEUR_ECRAN/4,HAUTEUR_ECRAN/4+HAUTEUR_ECRAN/8,LARGEUR_ECRAN/2,HAUTEUR_ECRAN/4);
	init_text(&(msg->score),"Score :",renderer,font,LARGEUR_ECRAN*5/8,0,LARGEUR_ECRAN/6,HAUTEUR_ECRAN/16);
	init_text(&(msg->score_chiffre),"0",renderer,font,LARGEUR_ECRAN*5/8+LARGEUR_ECRAN/6,0,LARGEUR_ECRAN/24,HAUTEUR_ECRAN/16);
	init_text(&(msg->best_score[0]),"The Bests Scores : ",renderer,font,LARGEUR_ECRAN/4,HAUTEUR_ECRAN/4,LARGEUR_ECRAN/2,HAUTEUR_ECRAN/8); 
	init_text(&(msg->best_score[1]),"1 st : ",renderer,font,(LARGEUR_ECRAN*5)/16,(HAUTEUR_ECRAN*7)/16,LARGEUR_ECRAN/8,HAUTEUR_ECRAN/8);
	init_text(&(msg->best_score[4]),"0",renderer,font,(LARGEUR_ECRAN*5)/16+LARGEUR_ECRAN/8,(HAUTEUR_ECRAN*7)/16,LARGEUR_ECRAN/24,HAUTEUR_ECRAN/8); 
	init_text(&(msg->best_score[2]),"2 nd : ",renderer,font,(LARGEUR_ECRAN*5)/16,(HAUTEUR_ECRAN*9)/16,LARGEUR_ECRAN/8,HAUTEUR_ECRAN/8);
	init_text(&(msg->best_score[5]),"0",renderer,font,(LARGEUR_ECRAN*5)/16+LARGEUR_ECRAN/8,(HAUTEUR_ECRAN*9)/16,LARGEUR_ECRAN/24,HAUTEUR_ECRAN/8);
	init_text(&(msg->best_score[3]),"3 th : ",renderer,font,(LARGEUR_ECRAN*5)/16,(HAUTEUR_ECRAN*11)/16,LARGEUR_ECRAN/8,HAUTEUR_ECRAN/8);
	init_text(&(msg->best_score[6]),"0",renderer,font,(LARGEUR_ECRAN*5)/16+LARGEUR_ECRAN/8,(HAUTEUR_ECRAN*11)/16,LARGEUR_ECRAN/24,HAUTEUR_ECRAN/8);
}

void update_message(text_t *text ,SDL_Renderer* renderer,TTF_Font *font,int chiffre)
{	
	char str [10];
	sprintf(str,"%d",chiffre);
	if (chiffre<= 9)
		init_text(text,str,renderer,font,LARGEUR_ECRAN*5/8+LARGEUR_ECRAN/6,0,LARGEUR_ECRAN/24,HAUTEUR_ECRAN/16);
	else if (chiffre <= 99)
		init_text(text,str,renderer,font,LARGEUR_ECRAN*5/8+LARGEUR_ECRAN/6,0,LARGEUR_ECRAN/18,HAUTEUR_ECRAN/16);
	else if (chiffre <= 999)
		init_text(text,str,renderer,font,LARGEUR_ECRAN*5/8+LARGEUR_ECRAN/6,0,LARGEUR_ECRAN/12,HAUTEUR_ECRAN/16);
	else 
		init_text(text,str,renderer,font,LARGEUR_ECRAN*5/8+LARGEUR_ECRAN/6,0,LARGEUR_ECRAN/12,HAUTEUR_ECRAN/16);

}

void clean_message(message_t *msg)
{
	SDL_DestroyTexture(msg->game_over.text);
	SDL_DestroyTexture(msg->you_win.text);
	SDL_DestroyTexture(msg->score.text);
	SDL_DestroyTexture(msg->score_chiffre.text);
	for(int i = 0 ; i<7 ; i++){
		SDL_DestroyTexture(msg->best_score[i].text);
	}


}

