#ifndef ABR_H
#define ABR_H

#include "truc.h"
#include "liste.h"

typedef struct _un_abr{
    Un_truc *truc; //La station
    struct _un_abr *g; //Sous arbre gauche

    struct _un_abr *d; //Sous arbre droit
} Un_abr;

void detruire_abr(Un_abr *abr);
Un_abr *construire_abr(Un_elem *liste_station);
Un_abr *inserer_abr(Un_abr **abr, Un_abr *noeud);
Un_abr *creer_abr(Un_truc *truc);
Un_truc *chercher_station(Un_abr *abr, char *nom);

#endif