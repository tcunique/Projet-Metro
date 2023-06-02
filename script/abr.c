#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abr.h"

Un_abr *creer_abr(Un_truc *truc){
    Un_abr *abr = (Un_abr *)malloc(sizeof(Un_abr));
    abr->truc = truc;
    abr->g = NULL;
    abr->d = NULL;
    return abr;
}

Un_abr *inserer_abr(Un_abr **abr, Un_abr *noeud){
    if(*abr == NULL){
        *abr = noeud;
    }
    else{
        if (strcmp((*abr)->truc->data.sta.nom, noeud->truc->data.sta.nom) > 0){
            inserer_abr(&((*abr)->g), noeud);
        }
        if (strcmp((*abr)->truc->data.sta.nom, noeud->truc->data.sta.nom) < 0){
            inserer_abr(&((*abr)->d), noeud);
        }
    }
    return *abr;
}

Un_abr *construire_abr(Un_elem *liste_station){
    Un_abr *abr = NULL;
    Un_elem *tmp = liste_station;
    while(tmp != NULL){
        Un_truc *truc = tmp->truc;
        Un_abr *noeud = creer_abr(truc);
        inserer_abr(&abr, noeud);
        tmp = tmp->suiv;
    }
    return abr;
}

void detruire_abr(Un_abr *abr){
    if(abr != NULL){
        detruire_abr(abr->g);
        detruire_abr(abr->d);
        free(abr);
    }
}

Un_truc *chercher_station(Un_abr *abr, char *nom){
    if (abr == NULL){
        return NULL;
    }
    else{
        if(strcmp(abr->truc->data.sta.nom, nom) == 0){
            return abr->truc;
        }
        else{
            if(strcmp(abr->truc->data.sta.nom, nom) > 0){
                return chercher_station(abr->g, nom);
            }
            else{
                return chercher_station(abr->d, nom);
            }
        }
    }
}
