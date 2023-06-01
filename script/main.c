#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "truc.h"
#include "liste.h"


int main(void){
    printf("Test 1 truc\n");
    printf("--------------------\n");

    Une_coord coord = {1.0, 2.0};

    Une_station station;
    station.nom = (char *)malloc(sizeof(char) * 10);
    strcpy(station.nom, "Station 1");

    Ttype type = STA;

    Tdata data;
    data.sta = station;

    Un_truc *truc = creer_truc(coord, type, data, 0.0);

    afficher_truc(truc);
    detruire_truc(truc);

    printf("\n");
    printf("Test 2 liste\n");
    printf("--------------------\n");
    Un_elem *liste = NULL;
    ecrire_liste(&liste);
    while (liste != NULL)
    {
        Un_elem *tmp = liste;
        liste = liste->suiv;
        afficher_truc(tmp->truc);
        printf("\n");
        detruire_truc(tmp->truc);
    }

    return 0;
}
