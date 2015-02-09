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
	result = REQUEST_OK;
	
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
		result = ERROR_400;
	}
	
	if (strcmp("/", res[1]) != 0)
	{
		result = ERROR_404;
	}
	
	free(res);
	return result;
}

void bad_request(const int ERROR, FILE * stream)
{
	char *error;
	if (ERROR == ERROR_400)
	{
		error = "400 Bad request\r\n";
	}
	else if (ERROR == ERROR_404)
	{
		error = "404 Not Found\r\n";
	}
	fprintf(stream, "HTTP/1.1 %s\r\nConnection: close\r\nContent-Length: %d\r\n\r\n%s", error, (int)strlen(error), error);
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
