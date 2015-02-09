#include "socket.h"
#include "http.h"

int main(int argc, char **argv)
{
	int port;
	int socket_serveur;
	int socket_client;
	int entete;
	char buf[256];
	FILE * stream;
	
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
			stream = fdopen(socket_client, "w+");
			print_request(fgets(buf, sizeof(buf), stream));
			
			/* Vérification de la ligne GET / HTTP/1.1 */
			entete = verifier_entete(buf);
			
			/* Attente de la ligne vide indiquant que la requête est terminée */
			while(strncmp("\r\n", fgets(buf, sizeof(buf), stream), 2) != 0)
			{
				print_request(buf);
			}
			
			if (entete != REQUEST_OK)
			{
				bad_request(entete, stream);
				fclose(stream);
				exit(0);
			}
			else
			{
				print_request("accepted\n");
				request_ok(stream);
			}
			
			while(1)
			{
				/* On lit le buffer */
				if (fgets(buf, sizeof(buf), stream) == NULL)
				{
					print_request("disconnected\n");
					fclose(stream);
					exit(0);
				}
				/* On écrit la requête du client sur la sortie standard du server */
				print_request(buf);
			}
		}
	}
	return 0;
}
