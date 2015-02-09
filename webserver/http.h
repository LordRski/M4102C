#ifndef __HTTP_H__
#define __HTTP_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <signal.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUEST_OK 0
#define ERROR_400 400
#define ERROR_404 404

/**
Vérifie l'en-tête de la requête envoyé par le client.
Retourne 0 si l'en-tête respecte les normes HTTP, -1 sinon.
*/
int verifier_entete(char * request);

/**
Affiche le message d'erreur "ERROR"
*/
void bad_request(const int ERROR, FILE * stream);

/**
Affiche le message de requête correcte
*/
void request_ok(FILE * stream);

/**
Affiche la requête dans la console serveur
*/
void print_request(char * request);
#endif
