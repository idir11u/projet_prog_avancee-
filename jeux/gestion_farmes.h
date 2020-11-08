/**
* \file  fonctios_SDL.h
* \author  Ait Aider Zinedine 
* \Brief bibliotheque fonctios_SDL. 
*/

#include<SDL2/SDL.h>
#ifndef  GESTION_FARMES_H
#define  GESTION_FARMES_H

typedef struct  frame_s 
{
	int cpt; //le numero de l'image actuel qu'on afffiche sur la ligne.  
	bool up;
	bool down;
	bool left;
	bool right;
};
typedef struct frame_s frame_t;


void init_farme(frame_t *frame);

#endif 