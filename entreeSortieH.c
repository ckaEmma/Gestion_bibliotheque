#include "biblioH.h"
#include "entreeSortieH.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BiblioH* charger_n_entreesH(const char* nomfic,int n){

    FILE *file=fopen(nomfic,"r");
    
    if(!file)
    {
        printf("Erreur d'ouverutre\n");
        exit(EXIT_FAILURE);
    }

    BiblioH *biblio= creer_biblioH(n*2);

    char buffer[256];
    int num;
    char auteur[100];
    char titre[100];

    for (int i=0;i<=n;i++)
    {   
        if (fgets(buffer,256,file)!=NULL)
        {
            if (sscanf(buffer,"%d %s %s",&num,titre,auteur)==3)
            {
               inserer(biblio,num,titre,auteur); 
            }else
            {
                printf("Format de donnee incorrect\n");
                exit(EXIT_FAILURE);
            }
        }else
        {
            printf("Probleme de lecture\n");
            exit(EXIT_FAILURE);
        }
        
        
    }

    fclose(file);

    return biblio;


}



void enregistrer_biblioH(BiblioH* biblio,const char *nomfic){
	if (biblio == NULL) {
        	printf("Bibliotheque vide, rien a enregistrer.\n");
        	return;
    	}

    	FILE* file = fopen(nomfic, "w");

    	if (!file) {
        	printf("Erreur d'ouverture\n");
        	exit(EXIT_FAILURE);
    	}

    	for (int i = 0; i < biblio->m; i++) {
        	LivreH* livreAEcrire = biblio->T[i];

        	while (livreAEcrire) {
            		fprintf(file, "%d %s %s\n", livreAEcrire->num, livreAEcrire->titre, livreAEcrire->auteur);
            		livreAEcrire = livreAEcrire->suivant;
        	}
    	}

    	fclose(file);

    	liberer_biblioH(biblio);
}
