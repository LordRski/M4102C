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

/**
Vérifie l'en-tête de la requête envoyé par le client.
Retourne 0 si l'en-tête respecte les normes HTTP, -1 sinon.
*/
int verifier_entete(char *request);

#endif
