#ifndef _TRUC_H_
#define _TRUC_H_

#include "coord.h"
#include "station.h"
#include "connexion.h"

typedef enum _ttype{STA, CON} Ttype;

typedef union _data{
    Une_station sta;
    Une_connexion con;
} Tdata;

typedef struct _un_truc {
    Une_coord coord; // Coordonnées GPS
    Ttype type;
    Tdata data;
    float user_val; //Distance du plus cours chemin
} Un_truc;


Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv);
void detruire_truc(Un_truc *truc);
void afficher_truc(Un_truc *truc);

#endif
