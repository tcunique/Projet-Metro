#ifndef ABR_H
#define ABR_H

#include "truc.h"

typedef struct _un_abr{
    Un_truc *truc; //La station
    struct _un_abr *g; //Sous arbre gauche

    struct _un_abr *d; //Sous arbre droit
} Un_abr;

#endif
