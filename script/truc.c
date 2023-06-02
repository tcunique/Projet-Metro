#include <stdio.h> 
#include <stdlib.h>
#include "truc.h"

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv){
    Un_truc *truc = (Un_truc *)malloc(sizeof(Un_truc));
    truc->coord = coord;
    truc->type = type;
    truc->data = data;
    truc->user_val = uv;
    return truc;
}

void detruire_truc(Un_truc *truc) {
    if (truc != NULL) {
        if (truc->type == STA) {
            if (truc->data.sta.nom != NULL) {
                free(truc->data.sta.nom);
            }
        }
    free(truc);
    }
}

void afficher_truc(Un_truc *truc){
    if (truc == NULL){
        printf("Truc NULL\n");
        return;
    }
    printf("Coordonnées : latitude = %lf, longitude = %lf\n", truc->coord.latitude, truc->coord.longitude);
    if(truc->type == STA){
        printf("Type : STA\n");
        printf("Nom : %s\n", truc->data.sta.nom);
    }
    else{
        printf("Type : CON\n");
        printf("Station de départ : %s\n", truc->data.con.sta_dep->data.sta.nom);
        printf("Station d'arrivée : %s\n", truc->data.con.sta_arr->data.sta.nom);
    }
    printf("User_val : %lf\n", truc->user_val);
}

