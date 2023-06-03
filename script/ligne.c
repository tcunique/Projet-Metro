#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "truc.h"
#include "ligne.h"

Une_ligne *lire_ligne(char *nom_fichier){
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL){
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }   

    char buffer[1024];
    Une_ligne *result = NULL;
    while (feof(f) == 0){
        fgets(buffer, 1024, f);

        Une_ligne *ligne = (Une_ligne *)malloc(sizeof(Une_ligne));
        if (ligne == NULL){
            printf("Erreur d'allocation de mémoire pour ligne\n");
            exit(1);
        }
        ligne->suiv = NULL;

        ligne->code = (char *)malloc(sizeof(char) * 10);
        ligne->color = (char *)malloc(sizeof(char) * 10);

        //Séparer les infos de la ligne dans le buffer
        char *info = strtok(buffer, ";");

        //Inscrit le code de la ligne dans la structure
        strcpy(ligne->code, info);
        ligne->code[strlen(ligne->code) -1] = '\0';

        //Inscrit la vitesse de la ligne dans la structure
        info = strtok(NULL, ";");
        ligne->vitesse = atoi(info);

        //Inscrit l'intervalle de la ligne dans la structure
        info = strtok(NULL, ";");
        ligne->intervalle = atoi(info);

        //Inscrit la couleur de la ligne dans la structure
        info = strtok(NULL, ";");
        strcpy(ligne->color, info);

        //Enlève le \n à la fin du nom de la ligne et l'espaces au début
        memmove(ligne->color, ligne->color + 1, strlen(ligne->color));
        ligne->color[strlen(ligne->color) - 1] = '\0';

        if (result == NULL){
            result = ligne;
        }
        else{
            Une_ligne *tmp = result;
            while (tmp->suiv != NULL){
                tmp = tmp->suiv;
            }
            tmp->suiv = ligne;
        }
    }
    fclose(f);
    return result;
}

void afficher_ligne(Une_ligne *liste_ligne){
    Une_ligne *tmp = liste_ligne;
    while (tmp != NULL){
        printf("Code : %s\n", tmp->code);
        printf("Vitesse : %f\n", tmp->vitesse);
        printf("Intervalle : %f\n", tmp->intervalle);
        printf("Couleur : %s\n", tmp->color);
        printf("\n");
        tmp = tmp->suiv;
    }
}

void detruire_ligne(Une_ligne *liste_ligne){
    Une_ligne *tmp = liste_ligne;
    while (tmp != NULL){
        Une_ligne *suiv = tmp->suiv;
        free(tmp);
        if (tmp->code != NULL){
            free(tmp->code);
        }
        if (tmp->color != NULL){
            free(tmp->color);
        }
        tmp = suiv;
    }
}

Une_ligne *chercher_ligne(Une_ligne *liste_ligne, char *code) {
    Une_ligne *tmp = liste_ligne;
    while (tmp != NULL){
        if (strcmp(tmp->code, code) == 0){
            return tmp;
        }
        tmp = tmp->suiv;
    }
    return NULL;
}