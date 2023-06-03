#ifndef AQRTOPO_H
#define AQRTOPO_H

#include "truc.h"

typedef struct _un_noeud{
    Un_truc *truc;
    
    Une_coord limite_no; //Limite Nord-Ouest
    Une_coord limite_se; //Limite Sud-Est

    struct _un_noeud *no; //Fils Nord-Ouest 
    struct _un_noeud *ne; //Fils Nord-Est
    struct _un_noeud *so; //Fils Sud-Ouest
    struct _un_noeud *se; //Fils Sud-Est
} Un_noeud;

Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc);
Un_noeud *construire_aqr(Un_elem *liste);
void detruire_aqr(Un_noeud *aqr);
Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord);
Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *liste, Une_coord limite_no, Une_coord limite_se);

#endif