#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "truc.h"
#include "liste.h"
#include "abr.h"
#include "ligne.h"
#include "aqrtopo.h"


int main(void){
    printf("Test 1 truc\n");
    printf("--------------------\n");

    Une_coord coord = {1.0, 2.0};

    Une_station station;
    station.nom = (char *)malloc(sizeof(char) * 10);
    station.tab_con = NULL;
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
    afficher_abr(abr);
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
    char *code = "1";
    Une_ligne *ligne2 = chercher_ligne(ligne, code);
    printf("Ligne 2 : \n");
    printf("Code : %s\n", ligne2->code);
    detruire_ligne(ligne);

    printf("\n");
    printf("Test 5\n");
    printf("--------------------\n");
    Un_elem *liste_station2 = NULL;
    ecrire_liste(&liste_station2);
    Un_abr *abr2 = construire_abr(liste_station2);
    Une_ligne *ligne3 = lire_ligne("ligne.csv");
    Un_elem *liste_connexion = lire_connexion("connexion.csv", ligne3, abr2);
    affiche_liste(liste_connexion);
    detruire_abr(abr2);
    detruire_liste_truc(liste_station2);
    detruire_ligne(ligne3);

    printf("\n");
    printf("Test 6\n");
    printf("--------------------\n");
    Un_elem *liste_station3 = NULL;
    ecrire_liste(&liste_station3);
    Un_noeud *aqr = construire_aqr(liste_station3);
    Une_coord coord1;
    coord1.latitude = 48.827080;
    coord1.longitude = 2.414945;

    Un_truc *truc4 = chercher_aqr(aqr, coord1);
    afficher_truc(truc4);

    Une_coord limite_no;
    limite_no.latitude = 48.852958; 
    limite_no.longitude = 2.344431; 
    Une_coord limite_se;
    limite_se.latitude = 48.827080;
    limite_se.longitude = 2.414945; 

    detruire_aqr(aqr);
    detruire_liste_truc(liste_station3);

    printf("\n");
    printf("Test 7\n");
    printf("--------------------\n");
    Un_elem *liste_station4 = NULL;
    ecrire_liste(&liste_station4);
    Un_abr *abr3 = construire_abr(liste_station4);
    Un_truc *truc5 = chercher_station(abr3, "La Défense - Grande Arche");
    dijkstra(liste_station4, truc5);
    affiche_liste(liste_station4);
    detruire_liste_truc(liste_station4);


    return 0;
}
