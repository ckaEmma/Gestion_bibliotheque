#ifndef _BIBLIOH_H_
#define _BIBLIOH_H_

typedef struct livreh
{
    int clef;
    int num;
    char* titre;
    char* auteur;
    struct livreh *suivant;
    
}LivreH;

typedef struct table
{
    int nE;
    int m;
    LivreH** T;
}BiblioH;

// FONCTION CLEF

int fonctionClef(char* auteur);

// FONCTION COMPARE

int compare_livreH(LivreH* livre1,LivreH* livre2);

// FONCTION CREATION

LivreH* creer_livreH(int num,char* titre,char* auteur);
LivreH* clone_livreH(LivreH* livre);
BiblioH* creer_biblioH(int m);

// FONCTION LIBERATION

void liberer_livreH(LivreH* livre);
void liberer_biblioH(BiblioH* biblio);
void supprimer_ouvrageH(BiblioH* biblio,int num,char* titre,char* auteur);

// FONCTION HACHAGE

int fonctionHachage(int clef,int m);

// FONCTION INSERTION

void inserer(BiblioH* biblio,int num,char* titre,char* auteur);

// FONCTION FUSION

void fusion_biblioH(BiblioH* biblio1, BiblioH* biblio2);

// FONCTIONS RECHERCHE

LivreH* recherche_par_numH(BiblioH* biblio,int num_recherche);
LivreH* recherche_par_titreH(BiblioH* biblio,char* titre);
BiblioH* recherche_par_auteurH(BiblioH* biblio,char* auteur_recherche);
BiblioH* recherche_exemplairesH(BiblioH* biblio);

// FONCTION AFFICHAGE 

void afficher_livreH(LivreH* l);
void afficher_biblioH(BiblioH* biblio);


#endif 
