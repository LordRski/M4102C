#include "url.h"

char * rewrite_url(char * url)
{
	char *rewrited;
	int i;
	
	i = 0;
	while (url[i] != '\0' && url[i] != '?')
	{
		i++;
	}
	
	rewrited = (char *)malloc(i+1);
	strncpy(rewrited, url, i);
	rewrited[i+1] = '\0';
	
	return rewrited;
}

int check_and_open(const char * url, const char * document_root)
{
	
	return -1;
}
