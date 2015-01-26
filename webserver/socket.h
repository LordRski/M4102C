#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Attend la connexion d'un utilisateur.

La fonction retourne -1 en cas d'erreur ou le descripteur de la socket créée.
*/
int ecouter_connexion(int socket_serveur);

/**
Crée une socket serveur qui écoute sur toute les interfaces IPv4 de la machine sur le port passé en paramètre.
La socket retournée doit pouvoir être utilisée directement par un appel à accept.

La fonction retourne -1 en cas d'erreur ou le descripteur de la socket créée.
*/
int creer_serveur(int port);

#endif
