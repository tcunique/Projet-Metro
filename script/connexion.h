#ifndef _CONNEXION_H_
#define _CONNEXION_H_

typedef struct _une_connexion {
    struct _un_truc *sta_dep; // Station de départ
    struct _un_truc *sta_arr; // Station d'arrivée

    struct _une_ligne *ligne; // Ligne empruntée
} Une_connexion;

#endif /* _CONNEXION_H_ */