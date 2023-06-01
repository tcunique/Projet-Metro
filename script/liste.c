#include <stdio.h>  
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "liste.h"

Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc)
{
    Un_elem *elem = (Un_elem *)malloc(sizeof(Un_elem));
    elem->truc = truc;
    elem->suiv = NULL;
    if ()
}

void ecrire_liste(Un_elem *liste){
    // On va ouvrir le fichier en mode lecture
    FILE *f = fopen("station.csv", "r");

    if (f == NULL)
    {
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }

    // On va lire le fichier ligne par ligne
    char buffer[1024];
    while (feof(f) == 0)
    {
        fgets(buffer, 1024, f);
        Un_elem *elem = (Un_elem *)malloc(sizeof(Un_elem));

        //Créer les variables pour le truc
        Une_coord coord;
        Une_station sta;
        Tdata data;
        Ttype type = STA;

        //On va séparer les données de la ligne
        char *ligne = strtok(buffer, ";");

        //On va remplir les variables
        coord.latitude = atof(ligne);
        ligne = strtok(NULL, ";");

        coord.longitude = atof(ligne);
        ligne = strtok(NULL, ";");

        sta.nom = ligne;

        //On crée l'élément et on le rajoute à la liste
        data.sta = sta;
        Un_truc *truc = creer_truc(coord, type, data, 0.0);
        elem->truc = truc;
        elem->suiv = NULL;
        liste = inserer_liste_trie(liste, truc);
        afficher_truc(elem->truc);
    }
    printf("\n");
}
