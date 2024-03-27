#include "biblioLC.h"
#include "entreeSortieLC.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Biblio* charger_n_entree(const char* nomfic,int n){

    FILE *file=fopen(nomfic,"r");
    
    if(!file)
    {
        printf("Erreur d'ouverture\n");
        exit(EXIT_FAILURE);
    }

    Biblio *biblio= creer_biblio();

    char buffer[256];
    int num;
    char auteur[100];
    char titre[100];

    for (int i=0;i<n;i++)
    {   
        if (fgets(buffer,256,file)!=NULL){
            if (sscanf(buffer,"%d %s %s",&num,titre,auteur)==3)
            {
               inserer_en_tete(biblio,num,titre,auteur); 
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


void enregistrer_biblio(Biblio* biblio,const char *nomfic){

    FILE* file=fopen(nomfic,"w");

    if(!file)
    {
        printf("Erreur d'ouverutre\n");
        exit(EXIT_FAILURE);
    }

    Livre* livreAEcrire=biblio->L;

    while (livreAEcrire)
    {
        fprintf(file,"%d %s %s\n",livreAEcrire->num,livreAEcrire->titre,livreAEcrire->auteur);
        livreAEcrire=livreAEcrire->suivant;
    }

    fclose(file);

    liberer_biblio(biblio);

}
