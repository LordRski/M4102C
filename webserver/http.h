#ifndef __HTTP_H__
#define __HTTP_H__

#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum http_method {
	HTTP_GET,
	HTTP_UNSUPPORTED,
};

typedef struct
{
	enum http_method method;
	int major_version;
	int minor_version;
	char *url;
} http_request;

/**
Afin de faciliter la gestion d’erreur, nous allons écrire une fonction qui lit les données en
provenance du client et quitte le processus si le client se déconnecte ou si une erreur survient.
*/
char * fgets_or_exit(char * buf, int size, FILE * stream);

/**
Vérifie l'en-tête de la requête envoyé par le client.
Retourne 0 si invalide, 1 sinon.
*/
int parse_http_request(const char * request_line, http_request * request);

/**
Passe les lignes d'en-tête qui ne sont pas obligatoire pour que la requête soit valide.
Une ligne entièrement vide indique que la requête est terminée.
*/
void skip_headers(FILE * client);

/**
Envoie le status de la requête au client.
*/
void send_status(FILE * client, int code, const char * reason_phrase);

/**
Envoie une réponse complète au client sur sa requête.
*/
void send_response(FILE * client, int code, const char * reason_phrase, const char * message_body);
#endif
