#ifndef _STATION_H_
#define _STATION_H_

typedef struct _une_station{
    char *nom; //Nom de la station
    struct _un_truc **tab_con; //Tableau de pointeurs sur les connexions

    unsigned int nb_con; //Nombre de connexions
    struct _un_truc *con_pcc; //Pointeur sur la connexion du plus court chemin
} Une_station;

#endif /* _STATION_H_ */