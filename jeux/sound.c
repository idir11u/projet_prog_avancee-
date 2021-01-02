#include "sound.h"
#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Chunk* init_son(const char* file_name)
{
	Mix_Chunk *son= Mix_LoadWAV(file_name);

	if(son==NULL)
	{
		fprintf(stderr, "Erreur chargement son", Mix_GetError());
	}
	return son;
}



void play_son(Mix_Chunk *son)
{
	Mix_PlayChannel(-1, son, 0);
}



Mix_Music* init_musique(const char* music_file)
{
	Mix_Music* music=Mix_LoadMUS(music_file);

	if(music==NULL)
	{
		fprintf(stderr, "Erreur chargement son", Mix_GetError());
	}
	return music;
}


void play_music(Mix_Music* music)
{
	Mix_PlayMusic(music, -1);
}

bruitages_t* init_bruitages()
{	
	bruitages_t *bruits=malloc(sizeof(bruitages_t));

	if(bruits==NULL)
	{
		printf("Allocation memoire echouee\n");
		exit(0);
	}
	bruits->clic = init_son("clic.wav");
	bruits->money = init_son("money.wav");
	bruits->gameover = init_son("gameover.wav");
	bruits->tresor = init_son("you_win.mp3");
	//bruits->help = init_son("you_win.wav");
	return bruits;
}


void clean_bruitage(bruitages_t* bruits)
{
	Mix_FreeChunk(bruits->clic);
    Mix_FreeChunk(bruits->money);
    Mix_FreeChunk(bruits->gameover);
	Mix_FreeChunk(bruits->tresor);
	//Mix_FreeChunk(bruits->help);
}	

