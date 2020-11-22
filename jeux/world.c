
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"
#include"gestion_terrain.h"
#include"world.h"
#include"constante.h"
#include"gestion_farmes.h"




void init_sprite(sprite_t * sprite,int h_terrain,int w_terrain,int x,int y,int large_img,int haut_img,int nbr_img_horis,int nbr_img_vetic)
{
	sprite->DestR_sprite.x = x;
	sprite->DestR_sprite.y = y;
	sprite->DestR_sprite.h = h_terrain;	
	sprite->DestR_sprite.w = w_terrain;
	sprite->SrcR_sprite.x = 0;
	sprite->SrcR_sprite.y = 0;
	sprite->SrcR_sprite.w = large_img/ nbr_img_horis;	
	sprite->SrcR_sprite.h = haut_img / nbr_img_vetic;
	init_farme(&(sprite->farme));
	sprite->est_visible = 1 ;                                 
}


void init_world(world_t *world)
{

	//il faut que ligne et colnne
	world->terminer = false ; 
	taille_fichier("terrain.txt",&(world->ligne),&(world->colonne));
	world->tab = lire_fichier("terrain.txt");
	init_terrain(&(world->terrain),world->ligne,world->colonne,world->tab);
	init_sprite(&(world->heros),world->terrain.DestR_terrain[0][0].h,world->terrain.DestR_terrain[0][0].w,0,0,LARGEUR_IMAGE_HEROS, HAUTEUR_IMAGE_HEROS,NBR_HORIS_IMAGE_HEROS , NBR_VERTIC_IMAGE_HEROS);
	init_terrain_avec_chemin(&(world->terrain),world->ligne,world->colonne ,world->tab,world->heros.DestR_sprite.x ,world->heros.DestR_sprite.y);
	world->indice_chemin_actuel = world->terrain.chemin.nbr_sommet/2 ;// pour l'ennemmy  ;
	world->aller_retour = 0;
	int y = world->terrain.DestR_terrain[0][0].h*(world->terrain.chemin.tab[world->indice_chemin_actuel]/world->colonne);//world->terrain.DestR_terrain[0][0].w * (world->terrain.chemin.tab[world->terrain.chemin.nbr_sommet/2]/world->colonne);
	int x = world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[world->indice_chemin_actuel]%world->colonne);//world->terrain.DestR_terrain[0][0].h * (world->terrain.chemin.tab[world->terrain.chemin.nbr_sommet/2]%world->colonne);
	init_sprite(&(world->ennemy),world->terrain.DestR_terrain[0][0].h,world->terrain.DestR_terrain[0][0].w,x,y,LARGEUR_IMAGE_HEROS, HAUTEUR_IMAGE_HEROS,NBR_HORIS_IMAGE_HEROS , NBR_VERTIC_IMAGE_HEROS);


}

void depacemnt_bordure(sprite_t* sprite,int Hauteur_ecran,int Largeur_ecran)
{

	if(sprite->DestR_sprite.x < 0)
		sprite->DestR_sprite.x = 0;
	if( sprite->DestR_sprite.x > Largeur_ecran-sprite->DestR_sprite.w)
		sprite->DestR_sprite.x = Largeur_ecran-sprite->DestR_sprite.w ;
	if (sprite->DestR_sprite.y<0)
		sprite->DestR_sprite.y = 0;
	if  (sprite->DestR_sprite.y> Hauteur_ecran-sprite->DestR_sprite.h)
		sprite->DestR_sprite.y = Hauteur_ecran-sprite->DestR_sprite.h;
}


bool collision_murs(sprite_t sprite, terrain_t terrain, int ligne, int colonne)
{
	int x1,x2,y1,y2;
	x1 = sprite.DestR_sprite.x + sprite.DestR_sprite.w/2;//l'abcsice du centre du sprite
	y1 = sprite.DestR_sprite.y + sprite.DestR_sprite.h/2;//l'ordonnée du centre du sprite
	for (int i = 0; i < ligne; ++i)
	{
		for (int j = 0; j < colonne; ++j)
		{
			if (terrain.SrcR_terrain[i][j].x !=0 || terrain.SrcR_terrain[i][j].y != 0 ) 
			 	if (terrain.SrcR_terrain[i][j].x != 32*3 || terrain.SrcR_terrain[i][j].y != 0 ) // differente de la terre
				{
					x2 = terrain.DestR_terrain[i][j].x + terrain.DestR_terrain[i][j].w/2; // l'abscice du centre du du mur(i,j) 
					y2 = terrain.DestR_terrain[i][j].y + terrain.DestR_terrain[i][j].h/2; // l'ordonnée du centre du du mur(i,j) 
					if (abs(x1-x2) < (sprite.DestR_sprite.w + terrain.DestR_terrain[i][j].w)/2)
						if (abs(y1-y2) < (sprite.DestR_sprite.h + terrain.DestR_terrain[i][j].h)/2)
							return true;
				}
		}
	}
	return false;	
}

void visible (sprite_t * sprite)
{
	sprite->est_visible = 1;
}

void invisible (sprite_t * sprite)
{
	sprite->est_visible = 0;
}

bool collision(sprite_t sprite_1,sprite_t sprite_2 )
{
	int x1,x2,y1,y2;
	x1 = sprite_1.DestR_sprite.x;
	x2 = sprite_2.DestR_sprite.x;
	y1 = sprite_1.DestR_sprite.y;
	y2 = sprite_2.DestR_sprite.y;
	if (abs(x1-x2) < (sprite_1.DestR_sprite.w +sprite_2.DestR_sprite.w)/4)
		if (abs(y1-y2) < (sprite_1.DestR_sprite.h + sprite_2.DestR_sprite.h)/4)
			return true;
	return false;
}

void demarche_ennemy(world_t *world)
{
	int x_prochain; // c'est pour trouver les cordoner du prchainn 
	int y_prochain; //

	if (world->aller_retour == 0)
	{
		y_prochain = world->terrain.DestR_terrain[0][0].h*(world->terrain.chemin.tab[world->indice_chemin_actuel-1]/world->colonne);
		x_prochain = world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[world->indice_chemin_actuel-1]%world->colonne);

		if (y_prochain != world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[0]/ world->colonne) ||  x_prochain != world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[0] % world->colonne))
		  {
			if(y_prochain != world->ennemy.DestR_sprite.y)
			{
					if(y_prochain>world->ennemy.DestR_sprite.y)
					{
						world->ennemy.DestR_sprite.y++;
						update_farmes(&(world->ennemy.farme),NBR_HORIS_IMAGE_HEROS,1,5);// 
						world->ennemy.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemy.farme.cpt;
						world->ennemy.SrcR_sprite.y = 0;

					}
					else if (y_prochain<world->ennemy.DestR_sprite.y)
					{
						world->ennemy.DestR_sprite.y--;
						//update_farmes(&(world->ennemy.farme),3,0) ;
						update_farmes(&(world->ennemy.farme),NBR_HORIS_IMAGE_HEROS,0,5);// 
						world->ennemy.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemy.farme.cpt;
						world->ennemy.SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-world->heros.SrcR_sprite.w;
					}
			}
			else if (x_prochain != world->ennemy.DestR_sprite.x)
			{
					if(x_prochain>world->ennemy.DestR_sprite.x)
					{
						world->ennemy.DestR_sprite.x++;
						//update_farmes(&(world->ennemy.farme),3,3) ;
						update_farmes(&(world->ennemy.farme),NBR_HORIS_IMAGE_HEROS,3,5);// 
						world->ennemy.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemy.farme.cpt;
						world->ennemy.SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-2*world->heros.SrcR_sprite.w ;
					}
					else if (x_prochain<world->ennemy.DestR_sprite.x)
					{
						world->ennemy.DestR_sprite.x--;
						//update_farmes(&(world->ennemy.farme),3,2) ;
						update_farmes(&(world->ennemy.farme),NBR_HORIS_IMAGE_HEROS,2,5);// 
						world->ennemy.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemy.farme.cpt;
						world->ennemy.SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-3*world->heros.SrcR_sprite.w ;
					}
			}
			if(y_prochain == world->ennemy.DestR_sprite.y && x_prochain == world->ennemy.DestR_sprite.x )
				world->indice_chemin_actuel = world->indice_chemin_actuel-1;
		}
		else 
		{
			world->indice_chemin_actuel = 1;
			world->aller_retour = 1 ;
		}

	}else if (world->aller_retour == 1)	
	{
		y_prochain = world->terrain.DestR_terrain[0][0].h*(world->terrain.chemin.tab[world->indice_chemin_actuel+1]/world->colonne);
		x_prochain = world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[world->indice_chemin_actuel+1]%world->colonne);

		if (y_prochain != world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[world->terrain.chemin.nbr_sommet-1]/ world->colonne) ||  x_prochain != world->terrain.DestR_terrain[0][0].w*(world->terrain.chemin.tab[world->terrain.chemin.nbr_sommet-1] % world->colonne))
		  {
			if(y_prochain != world->ennemy.DestR_sprite.y)
			{
					if(y_prochain>world->ennemy.DestR_sprite.y)
					{
						world->ennemy.DestR_sprite.y++;
						update_farmes(&(world->ennemy.farme),NBR_HORIS_IMAGE_HEROS,1,5);// 
						world->ennemy.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemy.farme.cpt;
						world->ennemy.SrcR_sprite.y = 0;
					}
					else if (y_prochain<world->ennemy.DestR_sprite.y)
					{
						world->ennemy.DestR_sprite.y--;
						//update_farmes(&(world->ennemy.farme),3,0) ;
						update_farmes(&(world->ennemy.farme),NBR_HORIS_IMAGE_HEROS,0,5);// 
						world->ennemy.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemy.farme.cpt;
						world->ennemy.SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-world->heros.SrcR_sprite.w;
					}
			}
			else if (x_prochain != world->ennemy.DestR_sprite.x)
			{
					if(x_prochain>world->ennemy.DestR_sprite.x)
					{
						world->ennemy.DestR_sprite.x++;
						//update_farmes(&(world->ennemy.farme),3,3) ;
						update_farmes(&(world->ennemy.farme),NBR_HORIS_IMAGE_HEROS,3,5);// 
						world->ennemy.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemy.farme.cpt;
						world->ennemy.SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-2*world->heros.SrcR_sprite.w ;
					}
					else if (x_prochain<world->ennemy.DestR_sprite.x){
						world->ennemy.DestR_sprite.x--;
						//update_farmes(&(world->ennemy.farme),3,2) ;
						update_farmes(&(world->ennemy.farme),NBR_HORIS_IMAGE_HEROS,2,5);// 
						world->ennemy.SrcR_sprite.x = (LARGEUR_IMAGE_HEROS/NBR_HORIS_IMAGE_HEROS)*world->ennemy.farme.cpt;
						world->ennemy.SrcR_sprite.y = HAUTEUR_IMAGE_HEROS-3*world->heros.SrcR_sprite.w ;
					}
			}
			if(y_prochain == world->ennemy.DestR_sprite.y && x_prochain == world->ennemy.DestR_sprite.x )
				world->indice_chemin_actuel = world->indice_chemin_actuel+1;
		}
		else 
		{
			world->indice_chemin_actuel = world->terrain.chemin.nbr_sommet-1 ;
			world->aller_retour = 0 ;
		}

	}

}


void update_world(world_t *world)
{
	depacemnt_bordure(&(world->heros),world->colonne*40,world->ligne*40);
	//world->ennemy.DestR_sprite.y = world->ennemy.DestR_sprite.y + 1;
	if (collision(world->heros,world->ennemy))
	{
		invisible(&(world->heros));
		invisible (&(world->ennemy));
	}
	
	if (world->ennemy.est_visible == 1)	
	{
		demarche_ennemy(world);
	}
}

void clean_world(world_t *world)
{
	desallouer_tab_2D(world->tab,world->ligne);
	desallouer_SDL_Renderer_terrain(&(world->terrain),world->ligne);
}


