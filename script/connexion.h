#ifndef _CONNEXION_H_
#define _CONNEXION_H_

#include "ligne.h"
typedef struct _un_truc Un_truc; // Forward declaration
typedef struct _un_abr Un_abr; // Forward declaration
typedef struct _un_elem Un_elem; // Forward declaration

typedef struct _une_connexion {
    struct _un_truc *sta_dep; // Station de départ
    struct _un_truc *sta_arr; // Station d'arrivée

    struct _une_ligne *ligne; // Ligne empruntée
} Une_connexion;

Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc);
Un_elem *lire_connexion(char *nom_fichier, Une_ligne *liste_ligne, Un_abr *abr_sta);

#endif /* _CONNEXION_H_ */