#include "biblioLC.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// FONCTIONS CREATION

Livre* creer_livre(int num,char* titre,char *auteur){

    Livre* livre=(Livre*)malloc(sizeof(Livre));

    if (livre==NULL)
    { 
        printf("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    livre->num=num;
    livre->auteur= strdup(auteur);
    livre->titre= strdup(titre);
    livre->suivant=NULL;

    return livre;
}

Biblio* creer_biblio(){
    Biblio* biblio=(Biblio*)malloc(sizeof(Biblio));
    if(biblio == NULL){
        printf("Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    biblio->L=NULL;
    return biblio;
}


// FONCTIONS LIBERATION

void liberer_livre(Livre *livre){
    if (!livre) return ;
    
    free(livre->auteur);
    free(livre->titre);
    free(livre);
}



void liberer_biblio(Biblio* biblio){

    if (!biblio) return ;

    Livre* entrainDeLibere=biblio->L;
    Livre* aLibere;

    while (entrainDeLibere)
    {
        aLibere=entrainDeLibere->suivant;
        liberer_livre(entrainDeLibere);
        entrainDeLibere=aLibere;
    }

    free(biblio);
    
}

void supprimer_ouvrage(Biblio* biblio,int num, char* titre, char* auteur){
	if (biblio==NULL) 
		return;

    	Livre* courant = biblio->L;
    	Livre* precedent = NULL;
    	int ouvrageTrouve = 0;

    	while (courant) {
        	if (courant->num == num && strcmp(courant->auteur, auteur) == 0 && strcmp(courant->titre, titre) == 0) {
            		ouvrageTrouve = 1;
            		if (precedent) {
                		precedent->suivant = courant->suivant;
                		liberer_livre(courant);
                		break;
            		} else {
                		biblio->L = courant->suivant;
                		liberer_livre(courant);
                		break;
            		}
        	}

        	precedent = courant;
        	courant = courant->suivant;
   	}

    	if (ouvrageTrouve==0) {
        	printf("L'ouvrage avec le numéro %d, le titre %s et l'auteur %s n'existe pas dans la bibliothèque.\n", num, titre, auteur);
    	}
}

// FONCTION INSERTION

void inserer_en_tete(Biblio* biblio,int num,char *titre,char* auteur){

    Livre* nv_livre= creer_livre(num,titre,auteur);
    nv_livre->suivant=biblio->L;
    biblio->L=nv_livre;

}

// FONCTION FUSION

void fusion_biblio(Biblio* b1, Biblio* b2){
    if (b1 == NULL || b2 == NULL) {
        return; // Vérifier si les pointeurs sont valides
    }

    Livre* current = b1->L; // Pointeur vers le premier livre de la première bibliothèque

    if (current == NULL) {
        b1->L = b2->L; // Si la première bibliothèque est vide, pointer vers la première de la deuxième
    } else {
        while (current->suivant != NULL) {
            current = current->suivant; // Trouver le dernier livre de la première bibliothèque
        }
        current->suivant = b2->L; // Lier le dernier livre de la première bibliothèque au premier livre de la deuxième
    }

    b2->L = NULL; // Vider la deuxième bibliothèque
}



// FONCTIONS DE RECHERCHE

Livre* recherche_par_num(Biblio* biblio,int num_recherche){

    Livre* livre_curr= biblio->L;

    while (livre_curr)
    {
        if (livre_curr->num==num_recherche)
        {
            return livre_curr;
        }
        livre_curr=livre_curr->suivant;
    }

    return NULL;
    
}

Livre* recherche_par_titre(Biblio* biblio,char* titre_recherche){

    Livre* livre_curr= biblio->L;

    while (livre_curr)
    {
        if (strcmp(livre_curr->titre,titre_recherche)==0)
        {
            return livre_curr;
        }
        
        livre_curr=livre_curr->suivant;
    }
    
    return NULL;

}


Biblio* recherche_par_auteur(Biblio* biblio,char* auteur_recherche){

    Livre* livre_curr=biblio->L;
    Biblio* biblio_auteur=creer_biblio();
    int auteur_trouve = 0;

    while (livre_curr)
    {
        if(strcmp(livre_curr->auteur,auteur_recherche)==0){
            inserer_en_tete(biblio_auteur,livre_curr->num,livre_curr->titre,livre_curr->auteur);
            auteur_trouve=1;
        }

        livre_curr=livre_curr->suivant;

    }

    if (auteur_trouve==1) {
        return biblio_auteur;
    } else {
        liberer_biblio(biblio_auteur); // Libérer la mémoire si aucun livre de l'auteur n'est trouvé
        return NULL;
    }
}

//fonction pour l'utiliser dans recherches_exemplaires
int recherche_livre(Biblio* biblio, Livre* livre_recherche) {
    Livre* livre_curr = biblio->L;

    while (livre_curr) {
        if (livre_curr->num == livre_recherche->num && strcmp(livre_curr->titre, livre_recherche->titre) == 0 && strcmp(livre_curr->auteur, livre_recherche->auteur) == 0) {
            return 1; // Livre trouvé
        }
        livre_curr = livre_curr->suivant;
    }

    return 0; // Livre non trouvé
}

Biblio* recherche_exemplaires(Biblio* biblio){
	printf("Je suis entré dans recherches\n");
    	Livre* livre_curr = biblio->L;

    	Biblio* biblio_exemplaire = creer_biblio();

    	while (livre_curr) {
        	Livre* livre_curr2 = biblio->L;
        	while (livre_curr2) {
            		if ((strcmp(livre_curr->titre,livre_curr2->titre)==0) && 
                (strcmp(livre_curr->auteur,livre_curr2->auteur)==0) && 
                (livre_curr->num != livre_curr2->num)) {
                
                // Vérifier si le livre n'est pas déjà dans la bibliothèque des exemplaires
                		if (recherche_livre(biblio_exemplaire, livre_curr)==0) {
                    			inserer_en_tete(biblio_exemplaire, livre_curr->num, livre_curr->titre, livre_curr->auteur);
               			 }
            		}
            		livre_curr2 = livre_curr2->suivant;
        	}
        	livre_curr = livre_curr->suivant;
    	}
    	printf("fin de la boucle\n");

    	return biblio_exemplaire;
}

// FONCTION D'AFFICHAGE

void afficher_livre(Livre* l){
	printf("%d : %s - %s\n",l->num,l->titre,l->auteur);
}

void afficher_biblio(Biblio* biblio){
    Livre* livre_curr=biblio->L;
	while(livre_curr){
		afficher_livre(livre_curr);
		livre_curr=livre_curr->suivant;
	}
}
