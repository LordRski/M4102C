#include "socket.h"

int main(int argc, char **argv)
{
	int port;
	int socket_serveur;
	int socket_client;
	int read_message;
	char buf[256];
	
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
			while(1)
			{
				/* On lit le buffer */
				read_message = read(socket_client, buf, sizeof(buf));
				if (read_message <= 0)
				{
					if (read_message == -1)
					{
						perror("read");
					}
					exit(0);
				}
		
				/* On écrit le message de l'utilisateur à l'utilisateur (echo) */
				if (write(socket_client, buf, read_message) != -1)
				{
					/* On notifie au serveur le message du client */
					buf[read_message] = '\0';
					printf("Client(id=%d) send: %s", getpid(), buf);
				}
			}
		}
	}
	return 0;
}
