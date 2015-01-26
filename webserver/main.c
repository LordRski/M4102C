#include "socket.h"

int main(int argc, char **argv)
{
	int port;
	int socket_serveur;
	int socket_client;
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
	
	socket_serveur = creer_serveur(port);
	
	if (socket_serveur == -1)
	{
		return -1;
	}
	
	socket_client = ecouter_connexion(socket_serveur);

	while(1)
	{
		/* On lit le buffer */
		if (read(socket_client, &buf, sizeof(buf)-1) <= 0)
		{
			socket_client = ecouter_connexion(socket_serveur);
		}
		
		/* On écrit le message de l'utilisateur à l'utilisateur (echo) */
		if (write(socket_client, &buf, strlen(buf)) == -1)
		{
			perror("write");
			return -1;
		}
		
		/* On notifie au serveur le message du client */
		printf("Client(id=%d) send: %s", socket_client, buf);
		
		/* On efface le buffer pour ne pas avoir de caractères résiduels */
		memset(&buf,0,255);
	}
	return 0;
}
