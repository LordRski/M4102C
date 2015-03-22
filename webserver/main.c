#include "headers/socket.h"
#include "headers/http.h"
#include "headers/url.h"
#include "headers/mime.h"
#include "headers/stats.h"

#define UPDATE(a) do { web_stats *stats = get_stats(); stats->(a++); release_stats(); } while (0)

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
	const char *document_root = "/home/infoetu/catteze/public_html";
	int port;
	int socket_serveur;
	int socket_client;
	int bad_request;
	int fd_file;
	char * url;
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
	
	/* Initialise les statistiques */
	init_stats();
	
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
		
		if (socket_client != 0 && socket_client != -1)
		{
			UPDATE(served_connections);
		
			client = fdopen(socket_client, "w+");
			
			while(1)
			{
				UPDATE(served_requests);
			
				/* Vérification de la ligne GET / HTTP/1.1 */
				bad_request = !parse_http_request(fgets_or_exit(buf, sizeof(buf), client), &request);
			
				/* Attente de la ligne vide indiquant que la requête est terminée */
				skip_headers(client);
			
				if (bad_request)
				{
					send_response(client, 400, "Bad Request", "Bad request\r\n");
					UPDATE(ko_404);
				}
				else if (request.method == HTTP_UNSUPPORTED)
				{
					send_response(client, 405, "Method Not Allowed", "Method Not Allowed\r\n");
				}
				else {
				
					if (strcmp(request.url, "/stats") == 0)
					{
						send_stats(client);
					}
					else
					{
						url = rewrite_url(request.url);
				
						if (url == NULL)
						{
							send_response(client, 403, "Forbidden", "Access denied\r\n");
							UPDATE(ko_403);
						}
						else {
							/* Ouverture et vérification du fichier à ouvrir au client */
							fd_file = check_and_open(url,document_root);
							
							if (fd_file == -1)
							{
								if (errno == EACCES)
								{
									send_response(client, 403, "Forbidden", "Access denied\r\n");
									UPDATE(ko_403);
								}
								else if (errno == EEXIST)
								{
									send_response (client, 404, "Not Found", "Not Found\r\n");
									UPDATE(ko_404);
								}
							}
							else {
								send_status(client, 200, "OK");
								send_content(client, get_mime(get_ext(url)));
								send_file(client, fd_file);
								UPDATE(ok_200);
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
