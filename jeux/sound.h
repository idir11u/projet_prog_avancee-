#ifndef SOUND_H
#define SOUND_H

#include "sound.h"
#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct bruitages_s
{
	Mix_Chunk* clic;
	Mix_Chunk* money;
	Mix_Chunk* gameover;
	Mix_Chunk* tresor;

}bruitages_t;

Mix_Chunk* init_son(const char* file_name);
void play_son(Mix_Chunk* son);

Mix_Music* init_musique(const char* music_file);
void play_music(Mix_Music* music);

bruitages_t* init_bruitages();

void clean_bruitage(bruitages_t* bruits);


#endif
