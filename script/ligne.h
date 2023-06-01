#ifndef LIGNE_H
#define LIGNE_H

typedef struct _une_ligne{
    char *code; //Code de la ligne

    char *color; //Couleur de la ligne
    float vitesse; //Vitesse moyenne des rames en km/h

    float intervalle; //Intervalle moyen entre 2 rames

    struct _une_ligne *suiv;
} Une_ligne;

#endif