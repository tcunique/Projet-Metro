#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aqrtopo.h"
#include "liste.h"


Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc)
{
    if (aqr == NULL)
    {
        aqr = (Un_noeud *)malloc(sizeof(Un_noeud));
        aqr->limite_no = limite_no;
        aqr->limite_se = limite_se;
        aqr->truc = truc;
        aqr->so = NULL;
        aqr->se = NULL;
        aqr->no = NULL;
        aqr->ne = NULL;
    }
    else
    {
        Une_coord coord = truc->coord;
        if (coord.longitude < (limite_no.longitude + limite_se.longitude) / 2)
        {
            if (coord.latitude < (limite_no.latitude + limite_se.latitude) / 2)
            {
                aqr->so = inserer_aqr(aqr->so, limite_no, limite_se, truc);
            }
            else
            {
                aqr->no = inserer_aqr(aqr->no, limite_no, limite_se, truc);
            }
        }
        else
        {
            if (coord.latitude < (limite_no.latitude + limite_se.latitude) / 2)
            {
                aqr->se = inserer_aqr(aqr->se, limite_no, limite_se, truc);
            }
            else
            {
                aqr->ne = inserer_aqr(aqr->ne, limite_no, limite_se, truc);
            }
        }
    }
    return aqr;
}

Un_noeud *construire_aqr(Un_elem *liste)
{
    Un_noeud *aqr = NULL;
    Une_coord limite_no;
    Une_coord limite_se;
    limites_zone(liste, &limite_no, &limite_se);
    while (liste != NULL)
    {
        aqr = inserer_aqr(aqr, limite_no, limite_se, liste->truc);
        liste = liste->suiv;
    }
    return aqr;
}

void detruire_aqr(Un_noeud *aqr)
{
    if (aqr != NULL)
    {
        detruire_aqr(aqr->so);
        detruire_aqr(aqr->se);
        detruire_aqr(aqr->no);
        detruire_aqr(aqr->ne);
        free(aqr);
    }
}

Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord)
{
    if (aqr == NULL)
    {
        return NULL;
    }
    else
    {
        if(aqr->truc->coord.latitude == coord.latitude && aqr->truc->coord.longitude == coord.longitude)
        {
            return aqr->truc;
        }
        if (coord.longitude < (aqr->limite_no.longitude + aqr->limite_se.longitude) / 2)
        {
            if (coord.latitude < (aqr->limite_no.latitude + aqr->limite_se.latitude) / 2)
            {
                return chercher_aqr(aqr->so, coord);
            }
            else
            {
                return chercher_aqr(aqr->no, coord);
            }
        }
        else
        {
            if (coord.latitude < (aqr->limite_no.latitude + aqr->limite_se.latitude) / 2)
            {
                return chercher_aqr(aqr->se, coord);
            }
            else
            {
                return chercher_aqr(aqr->ne, coord);
            }
        }
    }
}

Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *liste, Une_coord limite_no, Une_coord limite_se)
{
    if (aqr == NULL)
    {
        return NULL;
    }
    else
    {
        if (aqr->limite_no.latitude > limite_no.latitude && aqr->limite_no.longitude < limite_no.longitude && aqr->limite_se.latitude < limite_se.latitude && aqr->limite_se.longitude > limite_se.longitude)
        {
            liste = inserer_liste_trie(liste, aqr->truc);
        }
        liste = chercher_zone(aqr->so, liste, limite_no, limite_se);
        liste = chercher_zone(aqr->se, liste, limite_no, limite_se);
        liste = chercher_zone(aqr->no, liste, limite_no, limite_se);
        liste = chercher_zone(aqr->ne, liste, limite_no, limite_se);
        return liste;
    }
}