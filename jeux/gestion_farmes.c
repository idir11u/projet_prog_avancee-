#include <stdio.h>
#include <stdlib.h>
#include"gestion_farmes.h" 

void init_farme(farme_t *farme )
{
	farme->cpt = 0;
	farme->dist = 0; //par defaut on met la distination down
} 

void update_farmes(farme_t *farme,int nbr_image_horisental,int i)  // elle va etre appliquer si on a changer destination  
{
	if (farme->dist == i)
	{
		if (farme->cpt < nbr_image_horisental-1)//nbr_image_horisental)
			farme->cpt ++;
		else 
			farme->cpt = 0;
	}
	else // est la distination  i = 0 DOWN / i = 1 UP / i = 2 LEFT / i = 3  RIGHT.
	{
		if (i == 0)
		{
			farme->dist = 0;
		}
		else if(i == 1) 
		{
			farme->dist = 1;
		}
		else if(i == 2)
		{
			farme->dist = 2;
		}
		else if(i == 3)
		{
			farme->dist = 3;
		}
		farme->cpt = 0;
	}
}