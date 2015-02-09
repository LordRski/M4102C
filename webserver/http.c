#include "http.h"

int verifier_entete(char * request)
{	
	const int NB_WORDS = 3;
	char *tmp;
	char **res;
	char *split;
	int result;
	int words;
	
	tmp = request;
	res = NULL;
	split = strtok(tmp, " ");
	words = 0;
	result = 0;
	
	/* On découpe la requête et on stocke les parties dans res */
	while (split)
	{
		++words;
		res = realloc(res, sizeof(char*) * words);
		
		if (res == NULL)
		{
			return -1;
		}
		res[words-1] = split;
		split = strtok(NULL, " ");
	}
	
	/* La requête doit contenir exactement 3 mots */
	/* La requête doit commencer par GET */
	/* Vérifier que le 3ème mot est de la forme HTTP/M.m (M = 1, m = 0 ou 1) */
	if (words != NB_WORDS || strcmp("GET", res[0]) != 0 || (strncmp("HTTP/1.0", res[2], 8) != 0 && strncmp("HTTP/1.1", res[2], 8) != 0))
	{
		result = -1;
	}
	
	free(res);
	return result;
}

void bad_request_400(FILE * stream)
{
	const char *error = "400 Bad request\r\n";
	fprintf(stream, "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: %d\r\n\r\n%s", (int)strlen(error), error);
	fflush(stream);
}

void request_ok(FILE * stream)
{
	const char *welcome = "Bienvenue sur le serveur de la 7 Production\r\npar Melvin CLAVEL et Edouard CATTEZ\r\n\r\n";
	fprintf(stream, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s", (int)strlen(welcome), welcome);
	fflush(stream);
}

void print_request(char * request)
{
	printf("%d: %s", getpid(), request);
}
