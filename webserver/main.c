#include "socket.h"
#include "http.h"
#include "url.h"

char * fgets_or_exit(char * buf, int size, FILE * client)
{
	if (fgets(buf, size, client) == NULL)
	{
		fclose(client);
		exit(0);
	}
	return buf;
}

int main(int argc, char **argv)
{
	/*const char *motd = "Bienvenue sur le serveur de La 7 Production\r\npar Edouard CATTEZ et Melvin CLAVEL\r\n";*/
	const char *document_root = "/home/infoetu/catteze/public_html";
	int port;
	int socket_serveur;
	int socket_client;
	int bad_request;
	int fd_file;
	char buf[256];
	FILE * client;
	http_request request;
	
	if (argc < 2) {
		printf("Usage: /l7pserv [port]\n");
		return -1;
	}
	
	port = atoi(argv[1]);
	
	if (port == 0) {
		printf("Port must be an int > 0 !\n");
		return -1;
	}
	
	/* Initialise les signaux des processus */
	initialiser_signaux();
	
	/* Crée un serveur */
	socket_serveur = creer_serveur(port);
	
	if (socket_serveur == -1)
	{
		return -1;
	}
	
	while (1)
	{
		traitement_signal(socket_client);
		socket_client = ecouter_connexion(socket_serveur);
		if (socket_client != 0)
		{
			client = fdopen(socket_client, "w+");
			
			/* Vérification de la ligne GET / HTTP/1.1 */
			bad_request = !parse_http_request(fgets_or_exit(buf, sizeof(buf), client), &request);
			
			/* Attente de la ligne vide indiquant que la requête est terminée */
			skip_headers(client);
			
			if (bad_request)
				send_response(client, 400, "Bad Request", "Bad request\r\n");
			else if (request.method == HTTP_UNSUPPORTED)
				send_response(client, 405, "Method Not Allowed", "Method Not Allowed\r\n");
			else {
				fd_file = check_and_open(rewrite_url(request.url),document_root);
				if (fd_file == -1)
					send_response (client, 404, "Not Found", "Not Found\r\n");
				else {
					send_status(client, 200, "OK");
					send_file(client, fd_file);
				}
			}
			
			while(1)
			{
				fgets_or_exit(buf, sizeof(buf), client);
			}
		}
	}
	return 0;
}
