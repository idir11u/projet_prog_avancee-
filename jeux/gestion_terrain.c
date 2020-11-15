#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<SDL2/SDL.h>
#include"fonctions_fichiers.h"
#include"gestion_terrain.h"

/**
*Allocation de deux tableaux à 2 dimensions pour les deux champs de t    (DestR_terrain et SrcR_terrain) de taille ligne *colonne
*@param t une variable de type terrain_t
*@param ligne nombre de ligne du fichier qui a partir du quel on constuit le terrain
*@param colonne nombre de colonnr du fichier qui a partir du quel on constuit le terrain
*/

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
/**
*Desallocation de deux tableaux 2 dimensions de deux champs de t (DestR_terrain et t.SrcR_terrain) de taille ligne *colonne
*@param t une variable de type terrain_t
*@param ligne nombre de ligne du fichier qui a partir du quel on constuit le terrain
*/

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
/**
*Initialisation de deux tableaux à 2 dimensions pour les deux champs de t    (DestR_terrain et SrcR_terrain) de taille ligne *colonne a partir de tab
*@param t une variable de type terrain_t
*@param ligne nombre de ligne du fichier qui a partir du quel on constuit le terrain
*@param colonne nombre de colonne du fichier qui a partir du quel on constuit le terrain
*@param tab  tableau a 2 dimensions qui qu'ona initialisé a partir de la leture depuis le fichier 
*/

void init_terrain(terrain_t* t,int ligne,int colonne,char ** tab)
{
	creer_SDL_Renderer_terrain(t,ligne,colonne);
	for (int i = 0; i < ligne; i++)
	{
		for(int j=0; j<colonne; j++)
		{
			t->DestR_terrain[i][j].w = 40; // Largeur du sprite
			t->DestR_terrain[i][j].h = 40; // Hauteur du sprite
			t->DestR_terrain[i][j].x = t->DestR_terrain[i][j].w*j;
			t->DestR_terrain[i][j].y = t->DestR_terrain[i][j].h *i; 
			
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
