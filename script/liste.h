#ifndef _LISTE_H_
#define _LISTE_H_

#include "truc.h"

typedef struct _un_elem {
    Un_truc *truc;
    
    struct _un_elem *suiv;
} Un_elem;

Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc);
void ecrire_liste(Un_elem **liste);
void detruire_liste_truc(Un_elem *liste);
void affiche_liste(Un_elem *liste);
void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se);
Un_truc *extraire_liste(Un_elem **liste, Un_truc *truc);
Un_truc *extraire_deb_liste(Un_elem **liste);
void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep);

#endif /* _LISTE_H_ */