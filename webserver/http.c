#include "http.h"

int verifier_entete(char *request) {	
	/* Vérifier que la requête commence par GET et contient exactement 3 mots */
	/* Vérifier que le 3ème mot est de la forme HTTP/M.m (M = 1, m = 0 ou 1) */
	/* Ignorer les lignes non vides \r\n ou \n */
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
	
	if (spaces != NB_SPACES)
	{
		return -1;
	}
	
	if (strcmp("GET", res[0]) != 0)
	{
		return -1;
	}
	
	if (strcmp("HTTP/1.0", res[2]) != 0 && strcmp("HTTP/1.1", res[2]) != 0)
	{
		return -1;
	}
	
	return 0;
}
