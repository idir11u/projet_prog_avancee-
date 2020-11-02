#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<SDL2/SDL.h>
#include"fonctions_fichiers.h"
#include"gestion_terrain.h"


void creer_SDL_Renderer_terrain(terrain_t *t,int ligne, int colonne)
{
	t->DestR_terrain = malloc(ligne*sizeof(SDL_Rect*));
	for (int i = 0; i < ligne; ++i)
	{
		t->DestR_terrain[i] = malloc(colonne*sizeof(SDL_Rect));
	}

	t->SrcR_terrain = malloc(ligne*sizeof(SDL_Rect*));
	for (int i = 0; i < ligne; ++i)
	{
		t->SrcR_terrain[i] = malloc(colonne*sizeof(SDL_Rect));
	}

}

void desallouer_SDL_Renderer_terrain(terrain_t *t,int ligne)
{
	for (int i = 0; i < ligne; ++i)
	{
		free(t->DestR_terrain[i]);
	}
	free(t->DestR_terrain);
	for (int i = 0; i < ligne; ++i)
	{
		free(t->SrcR_terrain[i]);
	}
	free(t->SrcR_terrain);
}

void init_terrain(terrain_t* t,int ligne,int colonne,char ** tab)
{

	for (int i = 0; i < ligne; i++)
	{
		for(int j=0; j<colonne; j++)
		{
			
			t->DestR_terrain[i][j].x = 32*j;
			t->DestR_terrain[i][j].y = 32*i; 
			t->DestR_terrain[i][j].w = 32; // Largeur du sprite
			t->DestR_terrain[i][j].h = 32; // Hauteur du sprite
		}
	}

	for (int i = 0; i<ligne; i++)
	{
		for(int j=0; j<colonne; j++)
		{
			if (tab[i][j]== '0' )
				t->SrcR_terrain[i][j].x = 32*0;
			else if (tab[i][j]== '1')
				t->SrcR_terrain[i][j].x = 32*1;
			else if (tab[i][j]== '2')
				t->SrcR_terrain[i][j].x = 32*2;
			else if (tab[i][j]== '3')
				t->SrcR_terrain[i][j].x = 32*3;
			else if (tab[i][j]== '4')
				t->SrcR_terrain[i][j].x = 32*4;
			t->SrcR_terrain[i][j].y = 0;
			t->SrcR_terrain[i][j].w = 32;
			t->SrcR_terrain[i][j].h = 32;
		}
	}
}
