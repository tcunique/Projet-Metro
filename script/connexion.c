#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "connexion.h"
#include "liste.h"
#include "abr.h"

Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc)
{
    Un_elem *elem = (Un_elem *)malloc(sizeof(Un_elem));
    elem->truc = truc;
    elem->suiv = liste;
    return elem;
}


Un_elem *lire_connexion(char *nom_fichier, Une_ligne *liste_ligne, Un_abr *abr_sta)
{
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return NULL;
    }

    char buffer[512];
    Un_elem *liste = NULL;
    while (feof(f) == 0)
    {
        fgets(buffer, 512, f);
        char *ligne = strtok(buffer, ";");

        // On récupère le nom de la ligne 
        char *nom_ligne = ligne;
        nom_ligne[strlen(nom_ligne) -1] = '\0';

        // On récupère le nom de la station de départ
        ligne = strtok(NULL, ";");
        char *nom_sta_dep = ligne;
        // On enlève le premier caractère qui est un espace et le dernier qui est un retour à la ligne
        memmove(nom_sta_dep, nom_sta_dep + 1, strlen(nom_sta_dep));
        nom_sta_dep[strlen(nom_sta_dep) -1] = '\0';

        // On récupère le nom de la station d'arrivée
        ligne = strtok(NULL, ";");
        char *nom_sta_arr = ligne;
        // On enlève le premier caractère qui est un espace et le dernier qui est un retour à la ligne
        memmove(nom_sta_arr, nom_sta_arr + 1, strlen(nom_sta_arr));
        nom_sta_arr[strlen(nom_sta_arr) -1] = '\0';

        // On récupère le temps de trajet
        ligne = strtok(NULL, ";");
        float temps_trajet = atof(ligne);

        Un_truc *truc_sta_dep = chercher_station(abr_sta, nom_sta_dep);
        if (truc_sta_dep == NULL)
        {
            printf("Erreur lors de la recherche de la station %s\n", nom_sta_dep);
            return NULL;
        }
        Un_truc *truc_sta_arr = chercher_station(abr_sta, nom_sta_arr);
        if (truc_sta_arr == NULL)
        {
            printf("Erreur lors de la recherche de la station %s\n", nom_sta_arr);
            return NULL;
        }

        Une_ligne *ligne2 = chercher_ligne(liste_ligne, nom_ligne);
        if (ligne2 == NULL)
        {
            printf("Erreur lors de la recherche de la ligne %s\n", nom_ligne);
            return NULL;
        }
        if (temps_trajet == 0)
        {
            float distance = acos(sin(truc_sta_dep->coord.latitude) * sin(truc_sta_arr->coord.latitude) + cos(truc_sta_dep->coord.latitude) * cos(truc_sta_arr->coord.latitude) * cos(truc_sta_dep->coord.longitude - truc_sta_arr->coord.longitude)) * 6371;
            ligne2->intervalle = distance /ligne2->vitesse;
        }

        //On crée la connexion pour le tableau de connexion de la station de départ
        Une_connexion *con_dep = (Une_connexion *)malloc(sizeof(Une_connexion));
        con_dep->sta_dep = truc_sta_dep;
        con_dep->sta_arr = truc_sta_arr;
        con_dep->ligne = ligne2;
        Tdata data;
        data.con = *con_dep;
        Un_truc *truc = creer_truc(truc_sta_dep->coord, CON, data, 0);

        truc_sta_dep->data.sta.tab_con[truc_sta_dep->data.sta.nb_con] = truc;
        truc_sta_dep->data.sta.nb_con++;

        //On crée la connexion pour le tableau de connexion de la station d'arrivée
        Une_connexion *con_arr = (Une_connexion *)malloc(sizeof(Une_connexion));
        con_arr->sta_dep = truc_sta_arr;
        con_arr->sta_arr = truc_sta_dep;
        con_arr->ligne = ligne2;
        Tdata data2;
        data2.con = *con_arr;
        Un_truc *truc2 = creer_truc(truc_sta_arr->coord, CON, data2, 0);

        truc_sta_arr->data.sta.tab_con[truc_sta_arr->data.sta.nb_con] = truc2;
        truc_sta_arr->data.sta.nb_con++;

        //On insère une connexion dans la liste
        liste = inserer_deb_liste(liste, truc);
    }
    fclose(f);
    return liste;
}
