#include "http.h"

int parse_http_request(const char * request_line, http_request * request)
{
	const int NB_WORDS = 3;
	char *tmp;
	char **res;
	char *split;
	int words;
	
	tmp = alloca(strlen(request_line)+1);
	strcpy(tmp, request_line);
	res = NULL;
	split = strtok(tmp, " ");
	words = 0;
	
	request->method = HTTP_GET;	
	request->url = NULL;
	
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
		request->method = HTTP_UNSUPPORTED;
		free(res);
		return 0;
	}
	
	/* Version majeure de HTTP = 1 */
	request->major_version = 1;
	
	/* Version mineure de HTTP = 0 */
	if (strncmp("HTTP/1.0", res[2], 8) == 0)
	{
		request->minor_version = 0;
	}
	/* Version mineure de HTTP = 1 */
	else if (strncmp("HTTP/1.1", res[2], 8) == 0)
	{
		request->minor_version = 1;
	}
	
	/* Url de la requête */
	request->url = malloc(strlen(res[1])+1);
	strcpy(request->url, res[1]);
	
	free(res);
	return 1;
}

void skip_headers(FILE * client)
{
	char buf[256];
	/* Attente de la ligne vide indiquant que la requête est terminée */
	while(strncmp("\r\n", fgets_or_exit(buf, sizeof(buf), client), 2) != 0)
		;
}

void send_status(FILE * client, int code, const char * reason_phrase)
{
	fprintf(client, "HTTP/1.1 %d %s\r\n", code, reason_phrase);
	if (code != 200) {
		fprintf(client, "Connection: close\r\n");
	}
	fflush(client);
}

void send_response(FILE * client, int code, const char * reason_phrase, const char * message_body)
{
	send_status(client, code, reason_phrase);
	fprintf(client, "Content-Length: %d\r\n\r\n%s", (int)strlen(message_body), message_body);
	fflush(client);
}

void send_file(FILE * client, int fd) {
	int size;
	
	size = get_file_size(fd);
	
	fprintf(client, "Content-Length: %d\r\n\r\n", size);
	fflush(client);
	copy(fd, fileno(client));
	fflush(client);
}
