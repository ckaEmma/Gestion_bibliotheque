#ifndef _BIBLIOLC_H_
#define _BIBLIOLC_H_

typedef struct livre
{
    int num;
    char *titre;
    char *auteur;
    struct livre *suivant;
    
}Livre;

typedef struct 
{
    Livre *L;
}Biblio;


// FONCTIONS CREATION

Livre* creer_livre(int num,char* titre,char *auteur);
Biblio* creer_biblio();


// FONCTIONS LIBERATION

void liberer_livre(Livre *livre);
void liberer_biblio(Biblio* biblio);
void supprimer_ouvrage(Biblio* biblio,int num, char* titre, char* auteur);

// FONCTION INSERTION

void inserer_en_tete(Biblio* biblio,int num,char *titre,char* auteur);

// FONCTION FUSION

void fusion_biblio(Biblio* b1, Biblio* b2);

// FONCTION RECHERCHE

Livre* recherche_par_num(Biblio* biblio,int num_recherche);
Livre* recherche_par_titre(Biblio* biblio,char* titre_recherche);
Biblio* recherche_par_auteur(Biblio* biblio,char* auteur_recherche);
int recherche_livre(Biblio* biblio, Livre* livre_recherche);
Biblio* recherche_exemplaires(Biblio* biblio);

// FONCTION AFFICHAGE

void afficher_livre(Livre* l);
void afficher_biblio(Biblio* biblio);



#endif


