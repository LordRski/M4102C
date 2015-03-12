#ifndef __URL_H__
#define __URL_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Retourne l'url sans la partie Query succédant le caractère '?' (inclus).
*/
char * rewrite_url(char * url);

/**
La fonction doit s’assurer que le fichier est un fichier régulier, ouvrir le fichier en lecture seule et
retourner un descripteur vers ce fichier à l’aide de la fonction open. La fonction doit retourner -1
en cas d’erreur et un descripteur valide en cas de succès.
*/
int check_and_open(const char * url, const char * document_root);

/**
Retourne la taille d'un fichier déjà ouvert à partir de son descripteur.
*/
int get_file_size(int fd);

/**
Copie un fichier depuis le descripteur in vers le descripteur out.
Cette fonction est utilisée pour envoyer un fichier vers la socket client.
*/
int copy(int in, int out);


#endif
