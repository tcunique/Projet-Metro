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
    if (liste == NULL)
    {
        liste = elem;
    }
    else
    {
        Un_elem *tmp = liste;
        Un_elem *prec = NULL;
        while (tmp != NULL && tmp->truc->user_val < truc->user_val)
        {
            prec = tmp;
            tmp = tmp->suiv;
        }
        if (prec == NULL)
        {
            elem->suiv = liste;
            liste = elem;
        }
        else
        {
            prec->suiv = elem;
            elem->suiv = tmp;
        }
    }
    return liste;
}

void ecrire_liste(Un_elem **liste){
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
        if (elem == NULL) {
            printf("Erreur d'allocation de mémoire pour elem\n");
            exit(1);
        }

        //Créer les variables pour le truc
        Une_coord coord;
        Une_station sta;
        sta.nom = (char *)malloc(sizeof(char) * 256);
        Tdata data;
        Ttype type = STA;

        //On va séparer les données de la ligne
        char *ligne = strtok(buffer, ";");

        //On va remplir les variables
        coord.latitude = atof(ligne);
        ligne = strtok(NULL, ";");

        coord.longitude = atof(ligne);
        ligne = strtok(NULL, ";");

        strcpy(sta.nom, ligne);

        //On crée l'élément et on le rajoute à la liste
        data.sta = sta;
        Un_truc *truc = creer_truc(coord, type, data, 0.0);
        elem->truc = truc;
        elem->suiv = NULL;
        *liste = inserer_liste_trie(*liste, truc);
    }
}

void detruire_liste_truc(Un_elem *liste){
    while (liste != NULL)
    {
        Un_elem *tmp = liste;
        liste = liste->suiv;
        detruire_truc(tmp->truc);
        free(tmp);
    }
}

void affiche_liste(Un_elem *liste){
    while (liste != NULL)
    {
        afficher_truc(liste->truc);
        liste = liste->suiv;
    }
}

void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se){
    limite_no->latitude = liste->truc->coord.latitude;
    limite_no->longitude = liste->truc->coord.longitude;
    limite_se->latitude = liste->truc->coord.latitude;
    limite_se->longitude = liste->truc->coord.longitude;
    while (liste != NULL)
    {
        if (liste->truc->coord.latitude > limite_no->latitude)
        {
            limite_no->latitude = liste->truc->coord.latitude;
        }
        if (liste->truc->coord.longitude < limite_no->longitude)
        {
            limite_no->longitude = liste->truc->coord.longitude;
        }
        if (liste->truc->coord.latitude < limite_se->latitude)
        {
            limite_se->latitude = liste->truc->coord.latitude;
        }
        if (liste->truc->coord.longitude > limite_se->longitude)
        {
            limite_se->longitude = liste->truc->coord.longitude;
        }
        liste = liste->suiv;
    }
}