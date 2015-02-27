#ifndef __MIME_H__
#define __MIME_H__

#include <string.h>

struct ext_to_mime {
	const char * ext;
	const char * mime;
};

/**
Retourne l'extension de la requête utilisateur
*/
const char * get_ext(char * url);

/**
Retourne le mime associé à l'extension d'un fichier
*/
const char * get_mime(const char * ext);

#endif
