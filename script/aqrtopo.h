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

#endif