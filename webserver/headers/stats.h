#ifndef __STATS_H__
#define __STATS_H__

#include <stdio.h>
#include "http.h"

typedef struct
{
	int served_connections;
	int served_requests;
	int ok_200;
	int ko_400;
	int ko_403;
	int ko_404;
} web_stats;


/**
La fonction doit envoyer une réponse HTTP valide avec, pour l’instant, un contenu arbitraire.
Simple texte ou page html sans oublier d'adapter le type mime transmis au contenu généré.

Envoie des statistiques lorsque l'on choisit l'url "/stats"
*/
void send_stats(FILE * client);

/**
Initialise une variable globale de stats avec les champs initialisés à 0.
*/
int init_stats(void);

/**
Retourne un pointeur vers la variable globale de stats
*/
web_stats * get_stats(void);


#endif
