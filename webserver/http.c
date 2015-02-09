#include "http.h"

int verifier_entete(char * request)
{	
	const int NB_SPACES = 3;
	char *tmp;
	char **res;
	char *split;
	int spaces;
	
	tmp = request;
	res = NULL;
	split = strtok(tmp, " ");
	spaces = 0;
	
	/* On découpe la requête et on stocke les parties dans res */
	while (split)
	{
		++spaces;
		res = realloc(res, sizeof(char*) * spaces);	
		
		if (res == NULL)
		{
			return -1;
		}
		res[spaces-1] = split;
		split = strtok(NULL, " ");
	}
	
	/* On ajoute en dernière partie du split une valeur pour indiquer la fin de la découpe */
	res = realloc(res, sizeof(char*) * (spaces+1));
	if (res == NULL)
	{
		return -1;
	}
	res[spaces] = 0;
	
	/* La requête doit contenir exactement 3 mots */
	if (spaces != NB_SPACES)
	{
		return -1;
	}
	
	/* La requête doit commencer par GET */
	if (strcmp("GET", res[0]) != 0)
	{
		return -1;
	}
	
	/* Vérifier que le 3ème mot est de la forme HTTP/M.m (M = 1, m = 0 ou 1) */
	if (strncmp("HTTP/1.0", res[2], 8) != 0 && strncmp("HTTP/1.1", res[2], 8) != 0)
	{
		return -1;
	}
	
	return 0;
}

void bad_request_400(FILE * stream)
{
	fprintf(stream, "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n");
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
