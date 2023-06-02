#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "truc.h"
#include "liste.h"
#include "abr.h"
#include "ligne.h"


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
    affiche_liste(liste);
    detruire_liste_truc(liste);

    printf("\n");
    printf("Test 3 abr\n");
    printf("--------------------\n");
    Un_elem *liste_station = NULL;
    ecrire_liste(&liste_station);
    Un_abr *abr = construire_abr(liste_station);
    char *nom = "La Défense - Grande Arche";
    Un_truc *truc2 = chercher_station(abr, nom);
    Un_truc *truc3 = chercher_station(abr, "");
    afficher_truc(truc2);    
    afficher_truc(truc3);

    detruire_liste_truc(liste_station);
    detruire_abr(abr);

    printf("\n");
    printf("Test 4\n");
    printf("--------------------\n");
    Une_ligne *ligne = lire_ligne("ligne.csv");
    afficher_ligne(ligne);
    detruire_ligne(ligne);

    return 0;
}
