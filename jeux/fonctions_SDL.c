/**
* \file  fonctios_SDL.c
* \author  Ait Aider Zinedine && Idir Walid
* \Brief bibliotheque d'fonctios_SDL . 
*/

#include"fonctions_SDL.h"
	  
	/**
     * Chargement d'une image sur un rendu
     * @param nomFichier le nom de l'image au format Bitmap à charger 
     * @param renderer le rendu 
     * @return une texture contenant l'image chargée
     */
SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer)
{

	SDL_Surface *image =  SDL_LoadBMP(nomfichier);		//création d'une surface et chargement d'une image
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer ,image);	//Création de la texture associée à l'image (la surface)
	SDL_FreeSurface(image);			//liberation de la mémoire dédiée à la surface
	if (texture != NULL) 		//Test de réussite de l'allocation
		return texture ;
	printf("l'image n'a pas été chargée ");
	return NULL ;
}


	/**
	*Chargement d'une image transparente 
	*@param nomfichier le nom de l'image au format Bitmap à charger 
	*@param renderer le rendu
	*@param r le taux de rouge de la couleur à masquer
	*@param g le taux de vert de la couleur à masquer
	*@param b le taux de bleue de la couleur à masquer
	*@return l'image privée de la couleur souhaitée
	*/
SDL_Texture* charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface *image = NULL;
	SDL_Texture *texture = NULL;
	image = SDL_LoadBMP(nomfichier);	//Chargement de l'image 
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format,r,g,b)); 	//la valeur du pixel qui sera transparent 
	texture = SDL_CreateTextureFromSurface(renderer ,image); 	//Création de la texture à partir de l'image modifiée
	SDL_FreeSurface(image);			// libération de la mémoire
	return texture ;
}

	/**
	*Affichage de texte sur le rendu 
	*@param message le message à afficher
	*@param renderer le rendu
	*@param font la police de charactère 
	*@param color couleur de la police
	*@return l'image privée de la couleur souhaitée
	*/
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color) 
{
	SDL_Texture *texture = NULL;
	SDL_Surface *texte=NULL;		//création de la surface 
	texte = TTF_RenderText_Solid(font,message,color);	//écriture sur la surface
	texture = SDL_CreateTextureFromSurface(renderer ,texte);	//création de la texture à partir de la surface 
	free(texte);
	return texture ;

}
