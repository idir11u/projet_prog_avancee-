/**
* \file  fonctios_SDL.c
* \author  Ait Aider Zinedine 
* \Brief bibliotheque d'fonctios_SDL . 
*/

#include"fonctions_SDL.h"

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer)
{

	SDL_Surface *image =  SDL_LoadBMP(nomfichier);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer ,image);
	SDL_FreeSurface(image);
	if (texture != NULL) //si l'image est bien charger  elle renvoie la texture associé a l'image 
		return texture ;
	printf("l'image n'a pas été chargée ");
	return NULL ;
}

SDL_Texture* charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface *image = NULL;
	SDL_Texture *texture = NULL;
	image = SDL_LoadBMP(nomfichier);
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format,r,g,b));
	texture = SDL_CreateTextureFromSurface(renderer ,image); 
	SDL_FreeSurface(image);
	return texture ;
}
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color) 
{
	SDL_Texture *texture = NULL;
	SDL_Surface *texte ;
	texte = TTF_RenderText_Solid(font,message,color);
	texture = SDL_CreateTextureFromSurface(renderer ,texte);
	return texture ;

}
