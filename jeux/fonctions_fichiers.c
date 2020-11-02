#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"fonctions_fichiers.h"


char** allouer_tab_2D(int n, int m)
{
	char** tab = malloc(n*sizeof(char*));
	for(int i = 0 ; i<n ; i++)
	{
		tab[i] = malloc(m*sizeof(char));
	}
	return tab ;
}

void desallouer_tab_2D(char** tab, int n)
{
	for (int i=0 ; i<n ; i++)
	{
		free(tab[i]);
	}
	free(tab); 

}

void afficher_tab_2D(char** tab, int n, int m)
{
	for (int i = 0; i<n; i++)      
	{
		for (int j = 0; j<m ;j++)
			{
			printf("%c ",tab[i][j]);
		}
		printf("\n");
	}
}

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol)
{
	FILE* fichier = fopen(nomFichier,"r");
	int cpt_colonne=0;
	int cpt_ligne = 0; 
	char char_actuel,char_precedant;

	if (fichier != NULL)
    {
        do
        {
            char_actuel= fgetc(fichier);
            if (char_actuel == EOF)
            {
				if (*nbCol<cpt_colonne)
            		*nbCol = cpt_colonne;
				cpt_colonne = 0;
				if (char_precedant == '\n')
					cpt_ligne = cpt_ligne -1;
            	cpt_ligne++;
            }

            else if(char_actuel == '\n'){  
            	if (*nbCol<cpt_colonne)
            		*nbCol = cpt_colonne;
				cpt_colonne = 0;
				cpt_ligne++;           	}
           	else
           	{
           		cpt_colonne++;
           	}
           	char_precedant = char_actuel;
        }while (char_actuel != EOF);
        *nbLig= cpt_ligne;
        fclose(fichier);

    }
}

char** lire_fichier(const char* nomFichier)
{
	FILE* fichier =  fopen(nomFichier,"r");
	int nbr_ligne ;
	int nbr_colonne ;
	char  c ;

	taille_fichier(nomFichier,&nbr_ligne,&nbr_colonne);
	char** tab = allouer_tab_2D(nbr_ligne,nbr_colonne);
    for(int i = 0 ; i<nbr_ligne;i++)
    {
    	for (int j = 0; j < nbr_colonne; j++)
    	{
    			tab[i][j] = ' '; 
    	}
    }
    int i=0,j=0;

    if (fichier != 0){
    	while(c!=EOF){       		
        	c = fgetc(fichier);
	  	if (c == '\n' || c==EOF){
        		j=0;
        		i++;
        	}
        	else{
        		tab[i][j] = c;
        		j++;

        	}
       	}
 	}
	fclose(fichier);
	return tab;
}

char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau)
{
	char ** nv = allouer_tab_2D(n,m);
	for(int i=0;i<n;i++)
	{
		for (int j = 0; j< m;j++)
		{
			if(tab[i][j] == ancien)
				nv[i][j] = nouveau;
			else 
				nv[i][j] = tab[i][j];
		}
	}
	return nv;
}
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m)
{
	FILE* fichier =  fopen(nomFichier,"w");
	for(int i=0;i<n;i++)
	{
		for (int j = 0; j< m;j++)
		{
			fputc(tab[i][j],fichier);
		
		}
		fputc('\n',fichier);
	}

	fclose(fichier);
}