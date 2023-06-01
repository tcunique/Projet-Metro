#ifndef _LISTE_H_
#define _LISTE_H_

#include "truc.h"

typedef struct _un_elem {
    Un_truc *truc;
    
    struct _un_elem *suiv;
} Un_elem;

Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc);
void ecrire_liste(Un_elem *liste);

#endif /* _LISTE_H_ */