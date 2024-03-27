#include "biblioH.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define A (((float)sqrt(5)-1)/2)

// FONCTION CLEF

int fonctionClef(char* auteur){

    if (!auteur)
    {
        printf("Ateur Invalide\n");
        exit(EXIT_FAILURE);
    }

    int clef=0;
    int i=0;

    while (auteur[i]!='\0')
    {
        clef+=(int)auteur[i];
        i++;
    }

    return clef; 
    
}

// FONCTION COMPARE

int compare_livreH(LivreH* livre1,LivreH* livre2){

    if (strcmp(livre1->titre,livre2->titre)==0 && strcmp(livre1->auteur,livre2->auteur)==0)
    {
        if (livre1->num==livre2->num)
        {
            return 1;
        }else{
            return 2;
        }
    }

    return 0;

}
// FONCTIONS CREATION

LivreH* creer_livreH(int num,char* titre,char* auteur){

    // if (titre[0]=='\0' || auteur[0]=='\0')
    // {
    //     printf("creer_livreH: auteur ou titre invalide\n");
    //     return NULL;
    // }

    LivreH* livre=(LivreH*)malloc(sizeof(LivreH));

    if (!livre)
    { 
        printf("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    livre->num=num;
    livre->clef=fonctionClef(auteur);
    livre->auteur= strdup(auteur);
    livre->titre= strdup(titre);
    livre->suivant=NULL;

    return livre;
}

LivreH* clone_livreH(LivreH* livre){

    return creer_livreH(livre->num,livre->titre,livre->auteur);

}

BiblioH* creer_biblioH(int m){

    BiblioH* biblio=(BiblioH*)malloc(sizeof(BiblioH));

    if(biblio==NULL){
        printf("Erreur d'allocation de memoire\n");
        return NULL;
    }

    biblio->m=m;
    biblio->nE=0;
    biblio->T=(LivreH**)malloc(m*sizeof(LivreH*));


    for (int i=0;i<m;i++){
        biblio->T[i]=NULL;
    }

    return biblio;

}

// FONCTIONS LIBERATIONS

void liberer_livreH(LivreH* livre){

    if (!livre) return;
    
    free(livre->auteur);
    free(livre->titre);
    free(livre);

}

void liberer_biblioH(BiblioH* biblio){
    
    if (!biblio) return ;

    LivreH* livre_curr,*livre_temp;

    for (int i=0;i<biblio->m;i++){

        livre_curr=biblio->T[i];

        if (livre_curr!=NULL){

            while (livre_curr!=NULL)
            {
                livre_temp=livre_curr->suivant;
                liberer_livreH(livre_curr);
                livre_curr=livre_temp;
            }
            

        }
    }

    free(biblio->T);
    free(biblio);

}

void supprimer_ouvrageH(BiblioH* biblio,int num,char* titre,char* auteur){

    int clef_hache=fonctionHachage(fonctionClef(auteur),biblio->m);
    LivreH* livre_prec=NULL;
    LivreH* livre_curr=biblio->T[clef_hache];
    LivreH* livre_compare=creer_livreH(num,titre,auteur);

    while (livre_curr && compare_livreH(livre_curr,livre_compare)!=1)
    {
        livre_prec=livre_curr;
        livre_curr=livre_curr->suivant;
    }
    
    if(livre_curr)
    {
        if (!livre_prec)
        {
            biblio->T[clef_hache]=livre_curr->suivant;
            liberer_livreH(livre_curr);
        }else
        {
            livre_prec->suivant=livre_curr->suivant;
            liberer_livreH(livre_curr);
        }
    }

    liberer_livreH(livre_compare);

}
// FONCTION HACHAGE

int fonctionHachage(int clef,int m){

  return abs(m*(clef*A-abs(m*A)))%m;

}


// FONCTION INSERTION


void inserer(BiblioH* biblio,int num,char* titre,char* auteur){

    LivreH* livre_nv=creer_livreH(num,titre,auteur);
    int clef_hashe=fonctionHachage(livre_nv->clef,biblio->m);

    if(biblio->T[clef_hashe]==NULL)
    {
        biblio->T[clef_hashe]=livre_nv;
    }else
    {
      livre_nv->suivant=biblio->T[clef_hashe];
        biblio->T[clef_hashe]=livre_nv;  
    }
    

    biblio->nE++;

}

// FONCTION FUSION

void fusion_biblioH(BiblioH* biblio1, BiblioH* biblio2){

    LivreH* livre_curr;

    for (int i=0;i<biblio2->m;i++)
    {
        livre_curr=biblio2->T[0];

        while (livre_curr)
        {
            inserer(biblio1,livre_curr->num,livre_curr->titre,livre_curr->auteur);
            livre_curr=livre_curr->suivant;
        }
        
        
    }

    liberer_biblioH(biblio2);

}
// FONCTIONS RECHERCHE

LivreH* recherche_par_numH(BiblioH* biblio,int num_recherche){

    LivreH* livre_curr;
    
    for (int i=0;i<biblio->m;i++)
    {
        livre_curr=biblio->T[i];

        while (livre_curr)
        {
            if(livre_curr->num==num_recherche) return livre_curr;
            livre_curr=livre_curr->suivant;
        }
        
    }

    return NULL;

}

LivreH* recherche_par_titreH(BiblioH* biblio,char* titre){

    LivreH* livre_curr;

    for (int i=0;i<biblio->m;i++)
    {
        livre_curr=biblio->T[i];

        while (livre_curr)
        {
            if(strcmp(livre_curr->titre,titre)==0) return livre_curr;
            livre_curr=livre_curr->suivant;
        }
        
    }

    return NULL;
    
}


BiblioH* recherche_par_auteurH(BiblioH* biblio,char* auteur_recherche){

    int clef_hache=fonctionHachage(fonctionClef(auteur_recherche),biblio->m);
    BiblioH* biblio_auteur= creer_biblioH(2);
    LivreH* livre_curr=biblio->T[clef_hache];
    LivreH* clone;

    while (livre_curr)
    {
        if (strcmp(auteur_recherche,livre_curr->auteur)==0)
        {
            inserer(biblio_auteur,livre_curr->num,livre_curr->titre,livre_curr->auteur);
            // afficher_livreH(livre_curr);
        }

        livre_curr=livre_curr->suivant;
    }
    
    return biblio_auteur;

}

BiblioH* recherche_exemplairesH(BiblioH* biblio){

    if (!biblio){
        printf("recherche_exemplairesH: biblio vide\n");
        return NULL;
    }
    
    BiblioH* biblio_exemp = creer_biblioH(2);
    LivreH* livre_curr, *livre_compare;
    
    for (int i = 0; i < biblio->m; i++){
        livre_curr = biblio->T[i];
        
        while (livre_curr){
            livre_compare = biblio->T[i];
            int cpt = 0;
            
            while (livre_compare){
                if (livre_curr != livre_compare && compare_livreH(livre_curr, livre_compare) == 2){
                    cpt++;
                }
                livre_compare = livre_compare->suivant;
            }
            
            if (cpt > 0){
                inserer(biblio_exemp, livre_curr->num, livre_curr->titre, livre_curr->auteur);
            }
            
            livre_curr = livre_curr->suivant;
        }
    }
    
    return biblio_exemp;
}


// FONCTION AFFICHAGE

void afficher_livreH(LivreH* l){
    if (!l) return ;
	printf("%d : %s - %s\n",l->num,l->titre,l->auteur);
}

void afficher_biblioH(BiblioH* biblio){

    if (biblio==NULL)
    {
        printf ("afficher_biblioH: Biblio vide\n");
        return ;
    }

    LivreH* livre_curr;
    for (int i=0;i<biblio->m;i++)
    {   
        printf("%d----\n",i);
        livre_curr=biblio->T[i];
    
        while (livre_curr!=NULL)
        {   
            
            afficher_livreH(livre_curr);
            
            livre_curr=livre_curr->suivant;
        
        }
        
    }

}
