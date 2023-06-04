#include <stdio.h>  
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "liste.h"

#define INFINI 10000

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

        //Créer les variables pour le truc
        Une_coord coord;
        Une_station sta;
        sta.nom = (char *)malloc(sizeof(char) * 256);
        Tdata data;
        Ttype type = STA;

        //On va séparer les données de la ligne
        char *ligne = strtok(buffer, ";");

        //On va remplir les variables
        coord.longitude = atof(ligne);
        ligne = strtok(NULL, ";");

        coord.latitude = atof(ligne);
        ligne = strtok(NULL, ";");

        strcpy(sta.nom, ligne);
        //On supprime l'espace du début et \n de la fin
        memmove(sta.nom, sta.nom + 1, strlen(sta.nom));
        sta.nom[strlen(sta.nom) - 1] = '\0';

        sta.tab_con = (Un_truc **)malloc(sizeof(Un_truc *) * 10);
        sta.nb_con = 0;

        //On crée l'élément et on le rajoute à la liste
        data.sta = sta;
        Un_truc *truc = creer_truc(coord, type, data, 0.0);
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

Un_truc *extraire_deb_liste(Un_elem **liste){
    Un_truc *truc = NULL;
    if (*liste != NULL)
    {
        Un_elem *tmp = *liste;
        *liste = (*liste)->suiv;
        truc = tmp->truc;
        free(tmp);
    }
    return truc;
}

Un_truc *extraire_liste(Un_elem **liste, Un_truc *truc){
    Un_truc *truc_retour = NULL;
    if (*liste != NULL)
    {
        Un_elem *tmp = *liste;
        Un_elem *prec = NULL;
        while (tmp != NULL && tmp->truc != truc)
        {
            prec = tmp;
            tmp = tmp->suiv;
        }
        if (tmp != NULL)
        {
            if (prec == NULL)
            {
                *liste = tmp->suiv;
            }
            else
            {
                prec->suiv = tmp->suiv;
            }
            truc_retour = tmp->truc;
            free(tmp);
        }
    }
    return truc_retour;
}

void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep)
{
    Un_elem *liste_sta_tmp = liste_sta;
    while (liste_sta_tmp != NULL)
    {
        liste_sta_tmp->truc->user_val = INFINI;
        liste_sta_tmp = liste_sta_tmp->suiv;
    }
    sta_dep->user_val = 0.0;

    liste_sta_tmp = liste_sta;
    Un_truc *truc_courant = sta_dep;
    int user_val_courant = 0;
    while (liste_sta_tmp != NULL)
    {
        while (user_val_courant == truc_courant->user_val)
        {
            for (int i = 0; i < truc_courant->data.sta.nb_con; i++)
            {
                if (truc_courant->data.sta.tab_con[i]->user_val > truc_courant->user_val + 1)
                {
                    truc_courant->data.sta.tab_con[i]->user_val = truc_courant->user_val + 1;
                }
            }
            Un_elem *liste_parcours = liste_sta;
            while (liste_parcours != NULL)
            {
                if (liste_parcours->truc->user_val == user_val_courant)
                {
                    truc_courant = liste_parcours->truc;
                    break;
                }
                liste_parcours = liste_parcours->suiv;
            }

            if (liste_parcours == NULL)
            {
                extraire_liste(&liste_sta_tmp, truc_courant);
                user_val_courant++;
                liste_parcours = liste_sta;
                while (liste_parcours != NULL)
                {
                    if (liste_parcours->truc->user_val == user_val_courant)
                    {
                        truc_courant = liste_parcours->truc;
                        break;
                    }
                    liste_parcours = liste_parcours->suiv;
                }
            }
        }
    }
}